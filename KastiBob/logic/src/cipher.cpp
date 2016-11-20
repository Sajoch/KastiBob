#include "cipher.hpp"
#include <cstdlib>
#include <string.h>
#include "packet.hpp"
//RSA

RSAcipher::RSAcipher(const char* m, const char* e){
	mpz_init2(_m, 1024);
	mpz_init2(_e, 1024);
	mpz_set_str(_m, m, 10);
 	mpz_set_str(_e, e, 10);
}
void RSAcipher::encrypt(char* p){
	mpz_t plain, cipher;
	mpz_init2(plain, 1024);
	mpz_init2(cipher, 1024);
	mpz_import(plain, 128, 1, 1, 0, 0, p);
	mpz_powm(cipher, plain, _e, _m);
	size_t bcount = 128 - ((mpz_sizeinbase(cipher, 2) + 7) / 8);
	memset(p, 0, bcount);
	mpz_export(&p[bcount], NULL, 1, 1, 0, 0, cipher);
	mpz_clear(cipher);
	mpz_clear(plain);
}


//XTEA
XTEAcipher::XTEAcipher(){
	generateKeys();
}
XTEAcipher::XTEAcipher(uint32_t keys[4]){
	_keys[0] = keys[0];
	_keys[1] = keys[1];
	_keys[2] = keys[2];
	_keys[3] = keys[3];
}
uint32_t XTEAcipher::getKey(uint32_t idx){
	return _keys[idx];
}
void XTEAcipher::generateKeys(){
	_keys[0]=((rand()%0xff)<<24)|((rand()%0xff)<<16)|((rand()%0xff)<<8)|(rand()%0xff);
	_keys[1]=((rand()%0xff)<<24)|((rand()%0xff)<<16)|((rand()%0xff)<<8)|(rand()%0xff);
	_keys[2]=((rand()%0xff)<<24)|((rand()%0xff)<<16)|((rand()%0xff)<<8)|(rand()%0xff);
	_keys[3]=((rand()%0xff)<<24)|((rand()%0xff)<<16)|((rand()%0xff)<<8)|(rand()%0xff);
}
void XTEAcipher::encrypt(){

}
void XTEAcipher::decrypt(std::string& buf){
	uint32_t v0, v1;
	std::string retbuf;
	while(buf.size()>=8){
		v0 = NetworkPacket::peekUint32(buf);
		buf.erase(buf.begin(), buf.begin()+4);
		v1 = NetworkPacket::peekUint32(buf);
		buf.erase(buf.begin(), buf.begin()+4);
		uint32_t delta = 0x61C88647;
		uint32_t sum = 0xC6EF3720;
		for(int32_t i = 0; i < 32; i++) {
			v1 -= ((v0 << 4 ^ v0 >> 5) + v0) ^ (sum + _keys[sum>>11 & 3]);
			sum += delta;
			v0 -= ((v1 << 4 ^ v1 >> 5) + v1) ^ (sum + _keys[sum & 3]);
		}
		NetworkPacket::addUint32(retbuf, v0); 
		NetworkPacket::addUint32(retbuf, v1); 
	}
	buf = retbuf;
}
