#include <winsock2.h>
#include <iostream>
#include <string>
#include <gmp.h>

using namespace std;

class Packet{
	string buf;
public:
	Packet(){

	}
	void addUint8(uint8_t a){
		buf.push_back(a);
	}
	void addUint16(uint16_t a){
		buf.push_back(a&0xff);
		buf.push_back((a>>8)&0xff);
	}
	void addUint32(uint32_t a){
		buf.push_back((a)&0xff);
		buf.push_back((a>>8)&0xff);
		buf.push_back((a>>16)&0xff);
		buf.push_back((a>>24)&0xff);
	}
	void addString(string a){
		for(size_t i=0;i<a.size();i++)
			buf.push_back(a[i]);
	}
	uint32_t checksum(){
		const uint16_t MOD_ADLER=65521;
    uint8_t* data = (uint8_t*)buf.data();
    size_t len = buf.size();
    // algo
    uint32_t a = 1, b = 0;
    while (len > 0){
        size_t tlen = len > 5552 ? 5552 : len;
        len -= tlen;
        do{
            a += *data++;
            b += a;
        } while (--tlen);

        a %= MOD_ADLER;
        b %= MOD_ADLER;
    }
    return (b << 16) | a;
	}
	void add_header(){
		uint32_t crc = checksum();
		buf.insert(0, (char*)&crc, 4);
		uint16_t len = buf.size();
		buf.insert(0, (char*)&len, 2);
	}
	const char* getData(){
		return buf.data();
	}
	size_t getSize(){
		return buf.size();
	}
};

void RSAencrypt(char* msg){
	mpz_t plain,c, m_mod, m_e;
	mpz_init2(m_mod, 1024);
	mpz_init2(m_e, 1024);
	mpz_set_str(m_mod, "109120132967399429278860960508995541528237502902798129123468757937266291492576446330739696001110603907230888610072655818825358503429057592827629436413108566029093628212635953836686562675849720620786279431090218017681061521755056710823876476444260558147179707119674283982419152118103759076030616683978566631413", 10);
 	mpz_set_str(m_e, "65537", 10);

	mpz_init2(plain, 1024);
	mpz_init2(c, 1024);

	mpz_import(plain, 128, 1, 1, 0, 0, msg);

	mpz_powm(c, plain, m_e, m_mod);

	size_t count = (mpz_sizeinbase(c, 2) + 7)/8;
	memset(msg, 0, 128 - count);
	mpz_export(&msg[128 - count], NULL, 1, 1, 0, 0, c);

	mpz_clear(c);
	mpz_clear(plain);
}

int main(){
	WSADATA wsa;
  SOCKET s;
  sockaddr_in server;

  if (WSAStartup(MAKEWORD(2,2),&wsa) != 0){
      cout<<"Failed. Error Code : "<<WSAGetLastError()<<endl;
      return 1;
  }
  if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET){
      cout<<"Could not create socket : "<< WSAGetLastError()<<endl;
  }
  server.sin_addr.s_addr = inet_addr("91.134.189.246");
  server.sin_family = AF_INET;
  server.sin_port = htons( 7171 );

  if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
  {
      cout<<"connect error"<<endl;
      return 1;
  }

  Packet p;
	p.addUint8(1); //protocolID
	p.addUint16(2); //OS version
	p.addUint16(20007);//Tibia version
	p.addUint32(0x467FD7E6);//dat signature
	p.addUint32(0x467F9E74);//spr signature
	p.addUint32(0x4AE5C3D3);//pic signature
	string data;
	Packet pl;
	uint32_t keys[4];
	pl.addUint8(0);
	keys[0]=0x12345678;
	keys[1]=0x23456789;
	keys[2]=0x34567890;
	keys[3]=0x45678901;
	pl.addUint32(keys[0]);
	pl.addUint32(keys[1]);
	pl.addUint32(keys[2]);
	pl.addUint32(keys[3]);
	pl.addUint16(5);
	string login="dupad";
	string pass="dupad1";
	pl.addString(login);
	pl.addUint16(6);
	pl.addString(pass);
	data.append(pl.getData(), pl.getSize());
	data.resize(128);
	RSAencrypt(&data[0]);

	p.addString(data);
	p.add_header();
	cout<<"sending"<<endl;
	send(s, p.getData(), p.getSize(), 0);
	cout<<"send"<<endl;
	unsigned char bufferz[50001]={0};
	recv(s, (char*)bufferz, 50000, 0);
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
	//*/
	for(size_t i=0;i<len;i++){
		printf("0x%02x ",bufferz[i+6]);
	}
  return 0;
}
