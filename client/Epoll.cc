#include "Epoll.h"
#include <cstdlib>
#include <cstdio>

Epoll* Epoll::getInstance()
{
	if(!_epoll)
		_epoll=new Epoll();
	return _epoll;
}

Epoll::Epoll()
:_fd1(-1)
,_fd2(-1)
{
	_fd=epoll_create1(0);
	if(-1==_fd)
	{
		perror("epoll_create1()");
	}
}

Epoll::~Epoll()
{
}

Epoll* Epoll::_epoll=NULL;

void Epoll::addFd1(int fd,Task &task)
{
	if(_fd1!=-1)
		delFd1();
	struct epoll_event ev;
	ev.data.fd=fd;
	ev.events=EPOLLIN;
	int ret=epoll_ctl(_fd,EPOLL_CTL_ADD,fd,&ev);
	if(-1==ret)
	{
		perror("epoll_ctl(add)");
		exit(-1);
	}
	_fd1=fd;
	_task1=task;
}

void Epoll::addFd2(int fd,Task &task)
{
	if(_fd2!=-1)
		delFd2();
	struct epoll_event ev;
	ev.data.fd=fd;
	ev.events=EPOLLIN;
	int ret=epoll_ctl(_fd,EPOLL_CTL_ADD,fd,&ev);
	if(-1==ret)
	{
		perror("epoll_ctl(add)");
		exit(-1);
	}
	_fd2=fd;
	_task2=task;
}

void Epoll::delFd1()
{
	struct epoll_event ev;
	ev.data.fd=_fd1;
	ev.events=EPOLLIN;
	int ret=epoll_ctl(_fd,EPOLL_CTL_DEL,_fd1,&ev);
	if(-1==ret)
	{
		perror("epoll_ctl(del)");
		exit(-1);
	}
	_fd1=-1;
}

void Epoll::delFd2()
{
	struct epoll_event ev;
	ev.data.fd=_fd2;
	ev.events=EPOLLIN;
	int ret=epoll_ctl(_fd,EPOLL_CTL_DEL,_fd2,&ev);
	if(-1==ret)
	{
		perror("epoll_ctl(del)");
		exit(-1);
	}
	_fd2=-1;
}

void Epoll::wait()
{
	int epoll_num=epoll_wait(_fd,evs,2,-1);
	if(epoll_num>0)
	{
		int epoll_ev;
		for(epoll_ev=0;epoll_ev<epoll_num;++epoll_ev)
		{
			if(evs[epoll_ev].data.fd=_fd1 && evs[epoll_ev].events==EPOLLIN)
			{
				_task1();
			}
			if(evs[epoll_ev].data.fd=_fd2 && evs[epoll_ev].events==EPOLLIN)
			{
				_task2();
			}
		}	
	}
}

Epoll::Garbo::~Garbo()
{
	if(_epoll)
		delete _epoll;
}

Epoll::Garbo Epoll::_garbo;
