#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include "client.hpp"
#include <cstdlib>
#include <ctime>

using namespace std;


const char* Client::rsa_m_n = "109120132967399429278860960508995541528237502902798129123468757937266291492576446330739696001110603907230888610072655818825358503429057592827629436413108566029093628212635953836686562675849720620786279431090218017681061521755056710823876476444260558147179707119674283982419152118103759076030616683978566631413";
const char* Client::rsa_e_n = "65537";
uint32_t Client::dat_signature = 0x467FD7E6;
uint32_t Client::spr_signature = 0x467F9E74;
uint32_t Client::pic_signature = 0x4AE5C3D3;
uint32_t Client::mapViewX = 8;
uint32_t Client::mapViewY = 8;
int32_t Client::mapLayers = 15; //0-15 = 16 layers

