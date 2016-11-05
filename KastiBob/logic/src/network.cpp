#include "network.hpp"
#include <winsock2.h>
#include <iostream>

using namespace std;

NetworkManager::NetworkManager(std::string ip, uint16_t port, size_t maxdata){
	_maxdata = maxdata;
	if((sock = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET){
      //cout<<"Could not create socket : "<< WSAGetLastError()<<endl;
  }
	sockaddr_in server;
  server.sin_addr.s_addr = inet_addr("91.134.189.246");
  server.sin_family = AF_INET;
  server.sin_port = htons( 7171 );
	u_long iMode = 1;
  if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0){
      //cout<<"connect error"<<endl;
      return;
  }
	ioctlsocket(sock, FIONBIO, &iMode);
	recv_offset = 0;
	recv_buffer.resize(5120);
}
NetworkManager::~NetworkManager(){
	closesocket(sock);
}
void NetworkManager::addPacket(NetworkPacket& p){
	p.add_header();
	send_buffer.append(p.getData());
}
bool NetworkManager::getPacket(NetworkPacket& p){
	uint16_t len = 0;
	if (recv_offset >= 2) {
		len = (((recv_buffer[1]<<8)&0xff00) | (recv_buffer[0]&0xff)) + 2;
		if (recv_offset >= len) {
			p.buffer = recv_buffer.substr(0, len);
			recv_buffer.erase(recv_buffer.begin(), recv_buffer.begin()+len);
			return true;
		}
	}
	return false;
}
bool NetworkManager::tick() {
	if (send_buffer.size()) {
		int soff = send(sock, send_buffer.data(), send_buffer.size(), 0);
		if (soff > 0) {
			send_buffer.erase(send_buffer.begin(), send_buffer.begin()+soff);
		} else if (soff == 0) { //close
			//cout<<"close after send"<<endl;
			return false;
		} else if (soff == SOCKET_ERROR) {
			int error = WSAGetLastError();
			if(error != WSAEWOULDBLOCK){
				//cout<<"error after send "<<error<<endl;
				return false;
			}
		}
	}
	size_t rb_size = recv_buffer.size();
	if (rb_size > 51200) {
		return false;
	}
	if ((rb_size-recv_offset)<512) {
		recv_buffer.resize(1024+rb_size);
	}
	int roff = recv(sock, &recv_buffer[recv_offset], 512, 0);
	if (roff > 0) {
		recv_offset += roff;
	} else if (roff == 0) { //close
		//cout<<"close after recv"<<endl;
		return false;
	} else if (roff == SOCKET_ERROR) {
		int error = WSAGetLastError();
		if(error != WSAEWOULDBLOCK){
			//cout<<"error after recv "<<error<<endl;
			return false;
		}
	}
	return true;
}
