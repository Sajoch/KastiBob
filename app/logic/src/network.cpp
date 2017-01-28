#include "network.hpp"
#include <Poco/Net/NetException.h>
#include <Poco/AbstractObserver.h>
#include <iostream>

using namespace Poco::Net;

NetworkManager::NetworkManager(std::string ip):
addr(ip),
recv_offset(0)
{
	sock.connect(addr);
	sock.setBlocking(false);
	onPacketRecived = [](NetworkPacket&){};
	haveSize = false;
	force_close = false;
	thread.start(&NetworkManager::mainLoop, this);
}
NetworkManager::~NetworkManager(){
	force_close = true;
	thread.join();
}

void NetworkManager::mainLoop(void* data){
	NetworkManager* nm = (NetworkManager*)data;
	while(!nm->force_close){
		try{
			if(nm->sock.poll(0, Socket::SELECT_READ|Socket::SELECT_ERROR)){
				nm->onRead();
			}else if(nm->sock.poll(0, Socket::SELECT_WRITE)){
				nm->onWrite();
			}
		}catch(NetException e){
			return nm->onError();
		}
		Poco::Thread::yield();
	}
}
void NetworkManager::addPacketR(NetworkPacket& p){
	p.add_header();
	send_buffer.append(p.getData());
}
void NetworkManager::addPacket(NetworkPacket p){
	p.add_header();
	send_buffer.append(p.getData());
}


void NetworkManager::SetOnPacketRecived(std::function<void(NetworkPacket&)> cb){
	onPacketRecived = cb;
}

void NetworkManager::onRead(){
	int rsize = sock.available();
	int buffer_size = recv_buffer.size() - recv_offset;
	if(buffer_size<rsize){
		recv_buffer.resize(recv_buffer.size() + rsize);
	}
	int recvb = sock.receiveBytes(&recv_buffer[recv_offset], rsize);
	if(recvb > 0){
		recv_offset += recvb;
	}else{
		onDisconnect();
		return;
	}
	if(!haveSize && recv_offset >= 2){
		packet_size = NetworkPacket::peekUint16(recv_buffer);
		recv_buffer.erase(recv_buffer.begin(), recv_buffer.begin()+2);
		recv_offset -= 2;
		haveSize = true;
	}
	if(haveSize && !haveCrc && recv_offset >= 4){
		packet_crc = NetworkPacket::peekUint32(recv_buffer);
		recv_buffer.erase(recv_buffer.begin(), recv_buffer.begin()+4);
		recv_offset -= 4;
		packet_size -= 4;
		haveCrc = true;
	}
	if(haveSize && haveCrc && recv_offset >= packet_size){
		NetworkPacket p;
		p.buffer = recv_buffer.substr(0, packet_size);
		recv_offset -= packet_size;
		recv_buffer = recv_buffer.substr(recv_offset);
		haveSize = false;
		haveCrc = false;
		if(p.checksum() == packet_crc){
			onPacketRecived(p);
		}
	}
}
void NetworkManager::onWrite(){
	if(send_buffer.size()>0){
		int sendb = sock.sendBytes(send_buffer.data(), send_buffer.size());
		if(sendb > 0){
			send_buffer.erase(send_buffer.begin(), send_buffer.begin()+sendb);
		}
	}
}
void NetworkManager::onDisconnect(){
	force_close = true;
	std::cout<<"shutdown"<<std::endl;
}
void NetworkManager::onError(){
	force_close = true;
	std::cout<<"error"<<std::endl;
}
