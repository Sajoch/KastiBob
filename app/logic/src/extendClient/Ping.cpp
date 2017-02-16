#include "../extendClient.hpp"
#include "../client.hpp"
#include "../network.hpp"
#include "../packets/PingPacket.hpp"
#include <iostream>

void ExtendClient::Ping(NetworkPacket& p){
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	//_cast<std::chrono::microseconds>(end - start).count()
	int64_t diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - c->last_ping - std::chrono::seconds(5)).count();
	c->duration_between_pings = diff;
	c->last_ping = now;
	std::cout<<"ping: "<<c->duration_between_pings<<std::endl;
	c->conn->addPacket(PingPacket(c->xtea));
}
