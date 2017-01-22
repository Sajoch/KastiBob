#include "../extendClient.hpp"
#include "../packet.hpp"
#include "../client.hpp"
#include <iostream>

using namespace std;

void ExtendClient::ErrorMessage(NetworkPacket* p){
	if(p->getSize()<2 && p->getSize()<p->peakTStringSize()){
		c->disconnect("error message too short");
		return;
	}
	string error = p->getTString();
	cout<<"Error: "<<error<<endl;
}
