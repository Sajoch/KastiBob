#ifndef __NETWORK_HPP
#define __NETWORK_HPP

#include <string>
#include "packet.hpp"
#include <functional>
#include <chrono>
#include <mutex>
#define POCO_WIN32_UTF8
#include <Poco/Net/NetException.h>
#include <Poco/Thread.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/Socket.h>
#include <Poco/Net/StreamSocket.h>

class NetworkManager: public Poco::Net::SocketImpl{
	Poco::Net::SocketAddress addr;
	Poco::Net::StreamSocket sock;
	Poco::Thread thread;
	std::string send_buffer;
	size_t recv_offset;
	std::string recv_buffer;
	size_t _maxdata;
	uint16_t packet_size;
	uint32_t packet_crc;
	bool haveSize;
	bool haveCrc;
	bool force_close;
	bool running;
	std::mutex runningState;
	std::chrono::system_clock::time_point last;
	std::function<void(NetworkPacket&)> onPacketRecived;
	std::function<void(std::string)> onError;
	static void mainLoop(void* data);
	int onRead();
	int onWrite();
	void onDisconnect();
	void onSocketError(std::string e);
public:
	NetworkManager(std::string ip);
	~NetworkManager();
	void addPacket(NetworkPacket p);
	void addPacketR(NetworkPacket& p);
	void SetOnPacketRecived(std::function<void(NetworkPacket&)> cb);
	void SetOnError(std::function<void(std::string)> cb);
	void clearCallbacks();
};
#endif
