#include "network.hpp"
#include <Poco/Net/NetException.h>
#include <Poco/AbstractObserver.h>
#include <iostream>
using namespace std;
using namespace Poco::Net;

class SocketActivator{
	
};

NetworkManager::NetworkManager(std::string ip):
addr(ip),
recv_offset(0)
{
	sock.connect(addr);
	sock.setBlocking(false);
	onPacketRecived = [](NetworkPacket&){};
	haveSize = false;
	reactor.addEventHandler(sock, Poco::Observer<NetworkManager, ReadableNotification>(*this, &NetworkManager::onRead));
	reactor.addEventHandler(sock, Poco::Observer<NetworkManager, WritableNotification>(*this, &NetworkManager::onWrite));
	reactor.addEventHandler(sock, Poco::Observer<NetworkManager, ShutdownNotification>(*this, &NetworkManager::onShutdonw));
	reactor.addEventHandler(sock, Poco::Observer<NetworkManager, ErrorNotification>(*this, &NetworkManager::onError));
	reactor.addEventHandler(sock, Poco::Observer<NetworkManager, TimeoutNotification>(*this, &NetworkManager::onTimeout));
	thread.start(reactor);
	//waitForTerminationRequest();
	
}
NetworkManager::~NetworkManager(){
	sock.close();
	reactor.stop();
	//thread.join(0);
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


void NetworkManager::SetOnPacketRecived(std::function<void(NetworkPacket&)> cb){
	onPacketRecived = cb;
}

void NetworkManager::onRead(Poco::Net::ReadableNotification* nof){
	int rsize = sock.available();
	int buffer_size = recv_buffer.size() - recv_offset;
	if(buffer_size<rsize){
		recv_buffer.resize(recv_buffer.size() + rsize);
	}
	int recvb = sock.receiveBytes(&recv_buffer[recv_offset], rsize);
	if(recvb > 0){
		recv_offset += recvb;
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
void NetworkManager::onWrite(Poco::Net::WritableNotification* nof){
	if(send_buffer.size()>0){
		int sendb = sock.sendBytes(send_buffer.data(), send_buffer.size());
		cout<<"send"<<sendb<<"/"<<send_buffer.size()<<endl;
		if(sendb > 0){
			send_buffer.erase(send_buffer.begin(), send_buffer.begin()+sendb);
		}
	}
}
void NetworkManager::onShutdonw(Poco::Net::ShutdownNotification* nof){
	cout<<"shutdown"<<endl;
}
void NetworkManager::onError(Poco::Net::ErrorNotification* nof){
	cout<<"error"<<endl;
}
void NetworkManager::onTimeout(Poco::Net::TimeoutNotification* nof){
	cout<<"timeout"<<endl;
}


/*
bool NetworkManager::getPacket(NetworkPacket* p){
	
	return false;
}
int NetworkManager::tick() {
	int rsize;
	try{
		if(sock.poll(1, Socket::SELECT_ERROR)==true){
			return 1;
		} 
		else if(sock.poll(1, Socket::SELECT_WRITE)==true && send_buffer.size()>0){
			int sendb = sock.sendBytes(&send_buffer[0], send_buffer.size());
			cout<<"send"<<sendb<<endl;
			if(sendb > 0){
				send_buffer.erase(send_buffer.begin(), send_buffer.begin()+sendb);
			}
			return 0;
		} 
		else if(sock.poll(1, Socket::SELECT_READ)==true){
			
		}
	}catch(NetException e){
		cout<<"NetException"<<endl;
	}
	return 4;
}
*/
