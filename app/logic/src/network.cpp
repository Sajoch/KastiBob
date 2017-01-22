#include "network.hpp"
#include <Poco/Net/NetException.h>
#include <iostream>
using namespace std;
using namespace Poco::Net;

NetworkManager::NetworkManager(std::string ip):
addr(ip),
recv_offset(0)
{
	sock.connectNB(addr);
	haveSize = false;
}
NetworkManager::~NetworkManager(){
	sock.shutdown();
}
void NetworkManager::addPacketR(NetworkPacket& p){
	p.add_header();
	send_buffer.append(p.getData());
}
void NetworkManager::addPacket(NetworkPacket p){
	p.add_header();
	cout<<"add packet "<<p.getSize()<<endl;
	send_buffer.append(p.getData());
}
bool NetworkManager::getPacket(NetworkPacket* p){
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
		p->buffer = recv_buffer.substr(0, packet_size);
		recv_offset -= packet_size;
		recv_buffer = recv_buffer.substr(recv_offset);
		haveSize = false;
		haveCrc = false;
		if(p->checksum() == packet_crc){
			return true;
		}
	}
	return false;
}
int NetworkManager::tick() {
	int rsize;
	try{
		if(sock.poll(0, Socket::SELECT_ERROR)){
			return 1;
		} 
		else if(send_buffer.size()>0 && sock.poll(0, Socket::SELECT_WRITE)){
			int sendb = sock.sendBytes(&send_buffer[0], send_buffer.size());
			if(send > 0){
				send_buffer.erase(send_buffer.begin(), send_buffer.begin()+sendb);
			}
			return 0;
		} 
		else if(sock.poll(0, Socket::SELECT_READ)){
			rsize = sock.available();
			int buffer_size = recv_buffer.size() - recv_offset;
			if(buffer_size<rsize){
				recv_buffer.resize(recv_buffer.size() + rsize);
			}
			int recvb = sock.receiveBytes(&recv_buffer[recv_offset], rsize);
			if(recvb > 0){
				recv_offset += recvb;
				return 2;
			}else{
				return 1;
			}
		}
	}catch(NetException e){
		cout<<"NetException"<<endl;
	}
	return 4;
}
