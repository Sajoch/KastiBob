#include "../client.hpp"
#include "../extendClient.hpp"
#include "../packet.hpp"
#include <iostream>

using namespace std;

void ExtendClient::ErrorMessage(NetworkPacket& p){
	if(p.getSize()<2 && p.getSize()<p.peakTStringSize()){
		c->disconnect("error message too short");
		return;
	}
	string error = p.getTString();
<<<<<<< HEAD
	c->errorHandler(error, "ErrorMessage");
=======
	cout<<"Error: "<<error<<endl;
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa
}
