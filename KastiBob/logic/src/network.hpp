#ifndef __NETWORK_HPP
#define __NETWORK_HPP

#include <string>
#include "packet.hpp"

class NetworkManager{
	unsigned int sock;
	std::string send_buffer;
	size_t recv_offset;
	std::string recv_buffer;
	size_t _maxdata;
public:
	NetworkManager(std::string ip, uint16_t port, size_t maxdata);
	~NetworkManager();
	void addPacket(NetworkPacket& p);
	bool getPacket(NetworkPacket& p);
	bool tick();
};
#endif
