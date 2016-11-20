#ifndef __NETWORK_HPP
#define __NETWORK_HPP

#include <string>
#include "packet.hpp"
#define POCO_WIN32_UTF8
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/Socket.h"
#include "Poco/Net/StreamSocket.h"

class NetworkManager{
	Poco::Net::SocketAddress addr;
	Poco::Net::StreamSocket sock;
	std::string send_buffer;
	size_t recv_offset;
	std::string recv_buffer;
	size_t _maxdata;
	uint16_t packet_size;
	uint32_t packet_crc;
	bool haveSize;
	bool haveCrc;
public:
	NetworkManager(std::string ip);
	~NetworkManager();
	void addPacket(NetworkPacket p);
	void addPacket(NetworkPacket& p);
	bool getPacket(NetworkPacket& p);
	int tick();
};
#endif
