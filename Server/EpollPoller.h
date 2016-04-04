#ifndef _EPOLL_
#define _EPOLL_

#include "TcpConnection.h"
#include <sys/epoll.h>
#include <vector>
#include <map>
#include <functional>

using std::vector;
using std::function;
using std::map;

class TcpConnection;

class EpollPoller
{
public:
	typedef function<void(TcpConnectionPtr)> EpollPollerCallback;
	EpollPoller(int listenFd);

	void loop();
	void unloop();

	void setConnectionCallback(EpollPollerCallback cb);
	void setMessageCallback(EpollPollerCallback cb);
	void setCloseCallback(EpollPollerCallback cb);
private:
	void wait();
	void handleConnection();
	void handleMessage(int fd);
    int _epollFd;
	int _listenFd;
	bool _isLooping;
	vector<struct epoll_event> _event_vec;
	map<int,TcpConnectionPtr> _connection_map;

	EpollPollerCallback _onConnection;
	EpollPollerCallback _onMessage;
	EpollPollerCallback _onClose;

};

#endif
