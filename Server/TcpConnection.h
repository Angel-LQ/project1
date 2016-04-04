#ifndef _TCPCONNECTION_
#define _TCPCONNECTION_

#include "Noncopyable.h"
#include "Socket.h"
#include "SocketIO.h"
#include "InetAddress.h"
#include <string>
#include <memory>
#include <functional>

using std::string;
using std::shared_ptr;
using std::function;

class TcpConnection;
typedef shared_ptr<TcpConnection> TcpConnectionPtr;

class TcpConnection 
: Noncopyable
, public std::enable_shared_from_this<TcpConnection>
{
public:
	typedef shared_ptr<TcpConnection> TcpConnectionPtr;
	typedef function<void(TcpConnectionPtr)> TcpConnectionCallback;
	TcpConnection(int fd);
	~TcpConnection();

	void receive(string &msg);
	void send(const string &msg);
	void shutdown();

	string connectionMsg() const;

	void handleConnectionCallback();
	void handleMessageCallback();
	void handleCloseCallback();

	void setConnectionCallback(TcpConnectionCallback cb);
	void setMessageCallback(TcpConnectionCallback cb);
	void setCloseCallback(TcpConnectionCallback cb);

private:
	Socket _socket;
	SocketIO _socketIO;
	const InetAddress _localAddr;
	const InetAddress _peerAddr;
	bool _isShutdownWrite;

	TcpConnectionCallback _onConnectionCb;
	TcpConnectionCallback _onMessageCb;
	TcpConnectionCallback _onCloseCb;
};

#endif
