#include <winsock2.h>
#include <iostream>
#include <string>
#include "packets/LoginPacket.hpp"
#include "network.hpp"
#include <cstdlib>
#include <ctime>

using namespace std;


const char* rsa_m_m = "109120132967399429278860960508995541528237502902798129123468757937266291492576446330739696001110603907230888610072655818825358503429057592827629436413108566029093628212635953836686562675849720620786279431090218017681061521755056710823876476444260558147179707119674283982419152118103759076030616683978566631413";
const char* rsa_m_e = "65537";
uint32_t dat_signature = 0x467FD7E6;
uint32_t spr_signature = 0x467F9E74;
uint32_t pic_signature = 0x4AE5C3D3;

int main(){
	srand(time(0));
	WSADATA wsa;

  if (WSAStartup(MAKEWORD(2,2),&wsa) != 0){
      cout<<"Failed. Error Code : "<<WSAGetLastError()<<endl;
      return 1;
  }
	NetworkManager client("91.134.189.246", 7171, 51200);
	RSAcipher rsa(rsa_m_m, rsa_m_e);
	XTEAcipher xtea;
	LoginPacket login("dupad","dupad1", 20007, 2, rsa, xtea);
	client.addPacket(login);
	NetworkPacket p;
	bool state = true;
	while (state) {
		if(client.getPacket(p)){
			uint32_t crc = p.getUint32();
			
			cout<<"have"<<endl;
			break;
		}
		state = client.tick();
	}
	uint16_t len = (bufferz[1]<<8)&0xff00|(bufferz[0]&0xff);
	uint32_t crc = (bufferz[5]<<24)&0xff000000|(bufferz[4]<<16)&0xff0000|(bufferz[3]<<8)&0xff00|(bufferz[2]&0xff);
	uint32_t k[4] = {0};
	k[0] = keys[0];
	k[1] = keys[1];
	k[2] = keys[2];
	k[3] = keys[3];

	uint32_t* buffer = (uint32_t*)&bufferz[6];
	int read_pos = 0;

	int32_t messageLength = len;

	while(read_pos < messageLength/4){
		uint32_t v0 = buffer[read_pos], v1 = buffer[read_pos + 1];
		uint32_t delta = 0x61C88647;
		uint32_t sum = 0xC6EF3720;

		for(int32_t i = 0; i < 32; i++) {
			v1 -= ((v0 << 4 ^ v0 >> 5) + v0) ^ (sum + k[sum>>11 & 3]);
			sum += delta;
			v0 -= ((v1 << 4 ^ v1 >> 5) + v1) ^ (sum + k[sum & 3]);
		}
		buffer[read_pos] = v0; buffer[read_pos + 1] = v1;
		read_pos = read_pos + 2;
	}

	for(size_t i=0;i<len;i++){
		printf("(%c) 0x%02x ", bufferz[i+6], bufferz[i+6]);
	}
	//*/
  return 0;
}
