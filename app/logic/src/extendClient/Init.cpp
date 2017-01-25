#include "../extendClient.hpp"
#include "../client.hpp"
#include "../network.hpp"
#include "../packets/LoginPacket.hpp"

void ExtendClient::Init(NetworkPacket& p){
	if(p.getSize()<5){
		c->disconnect("parseInit too short");
		return;
	}
	for(int i=0;i<5;i++){
		c->verify_data[i] = p.getUint8();
	}
	//cout<<"login to game server"<<endl;
	c->xtea->generateKeys();
	c->xtea_crypted = true;
	c->conn->addPacket(
		LoginPacket(c->login, c->password,
			c->version, c->os,
			c->dat_signature, c->spr_signature, c->pic_signature,
			c->verify_data, c->current_character.getName(),
			c->rsa, c->xtea)
		);
}
