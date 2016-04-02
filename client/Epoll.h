#ifndef _EPOLL_
#define _EPOLL_

#include <sys/epoll.h>
#include <functional>

using std::function;

typedef function<void()> Task;

class Epoll
{
public:
	static Epoll* getInstance();
	void addFd1(int fd,Task &_task1);
	void addFd2(int fd,Task &_task2);
	void delFd1();
	void delFd2();
	void wait();
private:
	Epoll();
	~Epoll();
	static Epoll* _epoll;
    int _fd;
	int _fd1;
	int _fd2;
	Task _task1;
	Task _task2;
	struct epoll_event evs[2];

	class Garbo
	{
	public:
		~Garbo();
	};
	static Garbo _garbo;
};

#endif
