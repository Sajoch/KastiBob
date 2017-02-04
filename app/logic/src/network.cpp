#include "network.hpp"
#include <Poco/Net/NetException.h>
#include <Poco/Net/SocketImpl.h>
#include <Poco/AbstractObserver.h>
#include <iostream>

using namespace Poco::Net;

NetworkManager::NetworkManager(std::string ip):
addr(ip),
recv_offset(0)
{
	sock.connectNB(addr);
	//sock.setBlocking(false);
	clearCallbacks();
	haveSize = false;
	force_close = false;
	last = std::chrono::system_clock::now();
	thread.start(&NetworkManager::mainLoop, this);
}
NetworkManager::~NetworkManager(){
	runningState.lock();
	bool r = running;
	runningState.unlock();
	sock.close();
	force_close = true;
	if(r){
		thread.join();
	}
}

void NetworkManager::mainLoop(void* data){
	NetException error_store;
	int connectState;
	NetworkManager* nm = (NetworkManager*)data;
	nm->runningState.lock();
	nm->running = true;
	nm->runningState.unlock();
	connectState = 0;
	while(!nm->force_close){
		//std::cout<<"still in connection "<<nm->sock.impl()->socketError()<<std::endl;
		try{
			if(nm->sock.poll(0, Socket::SELECT_READ)){
				if(nm->onRead() != 0){
					std::cout<<"close thread after read"<<std::endl;
					connectState = 1;//nm->onDisconnect();
					break;
				}else{
					nm->last = std::chrono::system_clock::now();
				}
			}else if(nm->sock.poll(0, Socket::SELECT_WRITE)){
				if(nm->onWrite() != 0){
					std::cout<<"close thread after write"<<std::endl;
					connectState = 1;//nm->onDisconnect();
					break;
				}
			}else{
				std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
				int64_t diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - nm->last).count();
				nm->last = now;
				if(diff > 15000){
					std::cout<<"close thread after timeout"<<std::endl;
					connectState = 1;//nm->onDisconnect();
					break;
				}
			}
		}catch(NetException e){
			error_store = e;
			connectState = 2;//nm->onSocketError(e);
			break;
		}
		Poco::Thread::yield();
	}
	nm->runningState.lock();
	nm->running = false;
	nm->runningState.unlock();
	std::cout<<"endThread of connection"<<std::endl;
	if(connectState == 1){
		nm->onDisconnect();
	}else if(connectState == 2){
		nm->onSocketError(error_store);
	}
	//std::cout<<"endThread of connection - called cbs"<<std::endl;
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
void NetworkManager::SetOnError(std::function<void(std::string)> cb){
	onError = cb;
}
void NetworkManager::clearCallbacks(){
	onPacketRecived = [](NetworkPacket&){};
	onError = [](std::string){};
}

int NetworkManager::onRead(){
	int rsize = sock.available();
	int buffer_size = recv_buffer.size() - recv_offset;
	if(buffer_size<rsize){
		recv_buffer.resize(recv_buffer.size() + rsize);
	}
	int recvb = sock.receiveBytes(&recv_buffer[recv_offset], rsize);
	if(recvb > 0){
		recv_offset += recvb;
	}else{
		//onDisconnect();
		return 1;
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
	return 0;
}
int NetworkManager::onWrite(){
	if(send_buffer.size()>0){
		int sendb = sock.sendBytes(send_buffer.data(), send_buffer.size());
		if(sendb > 0){
			send_buffer.erase(send_buffer.begin(), send_buffer.begin()+sendb);
		}else{
			return 1;
		}
	}
	return 0;
}
void NetworkManager::onDisconnect(){
	force_close = true;
	onError("disconnected");
}
void NetworkManager::onSocketError(NetException e){
	force_close = true;
	onError(e.name());
}
