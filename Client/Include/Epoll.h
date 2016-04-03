#ifndef _EPOLL_
#define _EPOLL_

#include <sys/epoll.h>
#include <functional>

using std::function;

class SocketIO;

class Epoll
{
public:
	static Epoll* getInstance(int sfd,SocketIO &socketIO);
	void addFd1(int fd);
	void addFd2(int fd);
	void delFd1();
	void delFd2();
	void wait();
private:
	Epoll(int sfd,SocketIO &socketIO);
	~Epoll();
	static Epoll* _epoll;
    int _fd;
	int _fd1;
	int _fd2;
	SocketIO &_socketIO;
	struct epoll_event evs[2];

	class Garbo
	{
	public:
		~Garbo();
	};
	static Garbo _garbo;
};

#endif
