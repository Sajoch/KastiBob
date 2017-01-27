#ifndef __NETWORK_HPP
#define __NETWORK_HPP

#include <string>
#include "packet.hpp"
#include <functional>
#define POCO_WIN32_UTF8
#include "Poco/Thread.h"
#include "Poco/Net/SocketReactor.h"
#include "Poco/Net/SocketAcceptor.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/Socket.h"
#include "Poco/Net/StreamSocket.h"

class NetworkManager{
	Poco::Net::SocketAddress addr;
	Poco::Net::StreamSocket sock;
	Poco::Net::SocketReactor reactor;
	Poco::Thread thread;
	std::string send_buffer;
	size_t recv_offset;
	std::string recv_buffer;
	size_t _maxdata;
	uint16_t packet_size;
	uint32_t packet_crc;
	bool haveSize;
	bool haveCrc;
	std::function<void(NetworkPacket&)> onPacketRecived;
public:
	NetworkManager(std::string ip);
	~NetworkManager();
	void addPacket(NetworkPacket p);
	void addPacketR(NetworkPacket& p);
	void SetOnPacketRecived(std::function<void(NetworkPacket&)> cb);
	
	void onRead(Poco::Net::ReadableNotification* nof);
	void onWrite(Poco::Net::WritableNotification* nof);
	void onShutdonw(Poco::Net::ShutdownNotification* nof);
	void onError(Poco::Net::ErrorNotification* nof);
	void onTimeout(Poco::Net::TimeoutNotification* nof);
};
#endif
