#ifndef __NETWORK_HPP
#define __NETWORK_HPP

#include <string>
#include "packet.hpp"
#include <functional>
<<<<<<< HEAD
#include <chrono>
#include <mutex>
#define POCO_WIN32_UTF8
#include <Poco/Net/NetException.h>
#include <Poco/Thread.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/Socket.h>
#include <Poco/Net/StreamSocket.h>
=======
#define POCO_WIN32_UTF8
#include "Poco/Thread.h"
#include "Poco/Net/SocketReactor.h"
#include "Poco/Net/SocketAcceptor.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/Socket.h"
#include "Poco/Net/StreamSocket.h"
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa

class NetworkManager: public Poco::Net::SocketImpl{
	Poco::Net::SocketAddress addr;
	Poco::Net::StreamSocket sock;
<<<<<<< HEAD
=======
	Poco::Net::SocketReactor reactor;
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa
	Poco::Thread thread;
	std::string send_buffer;
	size_t recv_offset;
	std::string recv_buffer;
	size_t _maxdata;
	uint16_t packet_size;
	uint32_t packet_crc;
	bool haveSize;
	bool haveCrc;
<<<<<<< HEAD
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
=======
	std::function<void(NetworkPacket&)> onPacketRecived;
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa
public:
	NetworkManager(std::string ip);
	~NetworkManager();
	void addPacket(NetworkPacket p);
	void addPacketR(NetworkPacket& p);
	void SetOnPacketRecived(std::function<void(NetworkPacket&)> cb);
<<<<<<< HEAD
	void SetOnError(std::function<void(std::string)> cb);
	void clearCallbacks();
=======
	
	void onRead(Poco::Net::ReadableNotification* nof);
	void onWrite(Poco::Net::WritableNotification* nof);
	void onShutdonw(Poco::Net::ShutdownNotification* nof);
	void onError(Poco::Net::ErrorNotification* nof);
	void onTimeout(Poco::Net::TimeoutNotification* nof);
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa
};
#endif
