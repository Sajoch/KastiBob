#ifndef __CIPHER_HPP
#define __CIPHER_HPP

#include <gmp.h>
#include <cinttypes>
#include <string>

class RSAcipher{
	mpz_t _m, _e;
public:
	RSAcipher(const char* m, const char* e);
	void encrypt(char* p);
};

class XTEAcipher{
	uint32_t _keys[4];
public:
	XTEAcipher();
	XTEAcipher(uint32_t keys[4]);
	uint32_t getKey(uint32_t idx);
	void encrypt();
	void decrypt();
};
#endif
