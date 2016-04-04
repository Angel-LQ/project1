#include "EpollPoller.h"
#include "TcpConnection.h"
#include <assert.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

const int SIZE=1024;

int createEpollFd()
{
	int epollFd=epoll_create1(0);
	if(-1==epollFd)
	{
		perror("epoll_create1()");
	}
	return epollFd;
}

void addEpollFd(int epollFd,int fd)
{
	struct epoll_event ev;
	ev.data.fd=fd;
	ev.events=EPOLLIN;
	int ret=epoll_ctl(epollFd,EPOLL_CTL_ADD,fd,&ev);
	if(-1==ret)
	{
		perror("epoll_ctl(add)");
		exit(-1);
	}
}

size_t recvPeek(int sockfd, char * buff, size_t count)
{
	int nread;
	do
	{
		nread=recv(sockfd, buff, count, MSG_PEEK);
	}while(-1 == nread && errno == EINTR);
	return nread;

}
bool isConnectionClose(int sockfd)
{
	char buff[1024];
	int nread = recvPeek(sockfd,buff,1024);
	if(-1 == nread)
	{
		perror("recvPeek()");
		exit(-1);
	}
	return (0==nread);
}

void delEpollFd(int epollFd,int fd)
{
	struct epoll_event ev;
	ev.data.fd=fd;
	ev.events=EPOLLIN;
	int ret=epoll_ctl(epollFd,EPOLL_CTL_DEL,fd,&ev);
	if(-1==ret)
	{
		perror("epoll_ctl(del)");
		exit(-1);
	}
}

EpollPoller::EpollPoller(int listenFd)
:_epollFd(createEpollFd())
,_listenFd(listenFd)
,_isLooping(false)
,_event_vec(SIZE)
{
	addEpollFd(_epollFd,_listenFd);
}

void EpollPoller::loop()
{
	if(!_isLooping)
	{
		_isLooping=true;
		while(_isLooping)
			wait();	
	}
}

void EpollPoller::unloop()
{
	if(_isLooping)
		_isLooping=false;
}

void EpollPoller::wait()
{
	int event_num;
	do
	{
		event_num=epoll_wait(_epollFd,&(*_event_vec.begin()),_event_vec.size(),-1);		
	}while(event_num==-1 && errno==EINTR);
	if(-1==event_num)
	{
		perror("epoll_wair()");
		exit(-1);
	}
	else
	{
		if(event_num==static_cast<int>(_event_vec.size()))
			_event_vec.resize(event_num*2);
		for(int idx=0;idx!=event_num;++idx)
		{
			if(_event_vec[idx].data.fd==_listenFd)
			{
				if(_event_vec[idx].events==EPOLLIN)
				{
					handleConnection();
				}
			}
			else
			{
				if(_event_vec[idx].events==EPOLLIN)
				{
					handleMessage(_event_vec[idx].data.fd);		
				}
			}
		}
	}
}

void EpollPoller::handleConnection()
{
	int peerFd=accept(_listenFd,NULL,NULL);
	if(-1==peerFd)
	{
		perror("accept()");
		exit(-1);
	}
	addEpollFd(_epollFd,peerFd);
	TcpConnectionPtr pConn(new TcpConnection(peerFd));
	pConn->setConnectionCallback(_onConnection);
	pConn->setMessageCallback(_onMessage);
	pConn->setCloseCallback(_onClose);
	_connection_map[peerFd]=pConn;
	pConn->handleConnectionCallback();
}

void EpollPoller::handleMessage(int fd)
{
	bool isClosed=isConnectionClose(fd);
	auto it=_connection_map.find(fd);
	assert(it !=_connection_map.end());		

	if(isClosed)
	{
		it->second->handleCloseCallback();
		delEpollFd(_epollFd, fd);
		_connection_map.erase(it);
	}
	else
	{
		it->second->handleMessageCallback();
	}	
}

void EpollPoller::setConnectionCallback(EpollPollerCallback cb)
{
	_onConnection = cb;
}

void EpollPoller::setMessageCallback(EpollPollerCallback cb)
{
	_onMessage = cb;
}

void EpollPoller::setCloseCallback(EpollPollerCallback cb)
{
	_onClose = cb;
}
