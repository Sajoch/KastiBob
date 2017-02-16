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
	clearCallbacks();
	haveSize = false;
	force_close = false;
	running = true;
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
	std::string error_store;
	int connectState;
	int error = 0;
	NetworkManager* nm = (NetworkManager*)data;
	connectState = 0;
	std::cout<<"new connect"<<std::endl;
	nm->sock.connectNB(nm->addr);//, Poco::Timespan(1,0));
	nm->sock.setBlocking(false);
	std::cout<<"new connected"<<std::endl;
	while(!nm->force_close){
		try{
			error = nm->sock.impl()->socketError();
			if(error != 0){
				SocketImpl::error(error);
			}
			if(nm->sock.poll(1, Socket::SELECT_READ)){
				if(nm->onRead() != 0){
					std::cout<<"close thread after read"<<std::endl;
					connectState = 1;//nm->onDisconnect();
					break;
				}
			}
			if(nm->sock.poll(0, Socket::SELECT_WRITE)){
				if(nm->onWrite() != 0){
					std::cout<<"close thread after write"<<std::endl;
					connectState = 1;//nm->onDisconnect();
					break;
				}
			}
			Poco::Thread::yield();
		}catch(InvalidAddressException e){
			error_store = e.what();
			connectState = 2;//nm->onSocketError(e);
			break;
		}catch(InvalidSocketException e){
			error_store = e.what();
			connectState = 2;//nm->onSocketError(e);
			break;
		}catch(ServiceNotFoundException e){
			error_store = e.what();
			connectState = 2;//nm->onSocketError(e);
			break;
		}catch(ConnectionAbortedException e){
			error_store = e.what();
			connectState = 2;//nm->onSocketError(e);
			break;
		}catch(ConnectionResetException e){
			error_store = e.what();
			connectState = 2;//nm->onSocketError(e);
			break;
		}catch(ConnectionRefusedException e){
			error_store = e.what();
			connectState = 2;
			break;
		}catch(HostNotFoundException e){
			error_store = e.what();
			connectState = 2;
			break;
		}catch(NoAddressFoundException e){
			error_store = e.what();
			connectState = 2;//nm->onSocketError(e);
			break;
		}catch(InterfaceNotFoundException e){
			error_store = e.what();
			connectState = 2;//nm->onSocketError(e);
			break;
		}catch(NoMessageException e){
			error_store = e.what();
			connectState = 2;//nm->onSocketError(e);
			break;
		}catch(MessageException e){
			error_store = e.what();
			connectState = 2;//nm->onSocketError(e);
			break;
		}catch(...){
			error_store = "unknown error";
			connectState = 2;//nm->onSocketError(e);
			break;
		}
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
	//std::cout<<"read "<<recv_offset<<std::endl;
	while(recv_offset>0){
		//std::cout<<"recv_offset "<<recv_offset<<std::endl;
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
			recv_buffer = recv_buffer.substr(recv_offset);
			recv_offset = 0;
			haveSize = false;
			haveCrc = false;
			uint32_t crc = p.checksum();
			if(crc == packet_crc){
				//std::cout<<"rest "<<recv_offset<<std::endl;
				onPacketRecived(p);
				continue;
			}else{
				onError("no valid crc");
				std::cout<<"no valid crc "<<crc<<"="<<packet_crc<<std::endl;
			}
		}
		break;
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
void NetworkManager::onSocketError(std::string e){
	force_close = true;
	onError(e);
}
