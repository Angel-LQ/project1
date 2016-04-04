#include "Socket.h"
#include "InetAddress.h"
#include <cstdio>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

int createSocketFd()
{
	int fd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==fd)
	{
		perror("socket()");
	}
	return fd;
}

Socket::Socket()
:_fd(createSocketFd())
{
}

Socket::Socket(int fd)
:_fd(fd)
{
}

Socket::~Socket()
{
	close(_fd);
}

int Socket::fd()
{
	return _fd;
}

void Socket::shutdownWrite()
{
	int ret=shutdown(_fd,SHUT_WR);
	if(-1==ret)
	{
		perror("shutdown()");
		exit(-1);
	}
}

InetAddress Socket::getLocalAddr(int fd)
{
	struct sockaddr_in addr;
	socklen_t len=sizeof(struct sockaddr_in);
	int ret=getsockname(fd,(struct sockaddr*)&addr,&len);
	if(-1==ret)
	{
		perror("getsockname()");
	}
	return InetAddress(addr);
}

InetAddress Socket::getPeerAddr(int fd)
{
	struct sockaddr_in addr;
	socklen_t len=sizeof(struct sockaddr_in);
	int ret=getpeername(fd,(struct sockaddr*)&addr,&len);
	if(-1==ret)
	{
		perror("getpeername()");
	}
	return InetAddress(addr);
}

void Socket::get(InetAddress & addr,int num)
{
	setReuseAddrIs(true);
	setReusePortIs(true);
	setTcpNoDelayIs(true);
	setKeepAliveIs(true);
	bindWith(addr);
	listenTo(num);
}

int Socket::acceptFor()
{
	int peerfd=::accept(_fd,NULL,NULL);
	if(-1==peerfd)
	{
		perror("accept()");
	}
	return peerfd;
}

void Socket::setTcpNoDelayIs(bool flag)
{
	int on=flag?1:0;
	int ret=setsockopt(_fd,IPPROTO_TCP,TCP_NODELAY,&on,static_cast<socklen_t>(sizeof(on)));
	if(-1==ret)
	{
		perror("setsockopt(tcpnodelay)");
		close(_fd);
		exit(-1);
	}
}

void Socket::setReuseAddrIs(bool flag)
{
	int on=flag?1:0;
	int ret=setsockopt(_fd,SOL_SOCKET,SO_REUSEADDR,&on,static_cast<socklen_t>(sizeof(on)));
	if(-1==ret)
	{
		perror("setsockopt(reuseaddr)");
		close(_fd);
		exit(-1);
	}
}

void Socket::setReusePortIs(bool flag)
{
	int on=flag?1:0;
	int ret=setsockopt(_fd,SOL_SOCKET,SO_REUSEPORT,&on,static_cast<socklen_t>(sizeof(on)));
	if(-1==ret)
	{
		perror("setsockopt(reuseport)");
		close(_fd);
		exit(-1);
	}
}

void Socket::setKeepAliveIs(bool flag)
{
	int on=flag?1:0;
	int ret=setsockopt(_fd,SOL_SOCKET,SO_KEEPALIVE,&on,static_cast<socklen_t>(sizeof(on)));
	if(-1==ret)
	{
		perror("setsockopt(keepalive)");
		close(_fd);
		exit(-1);
	}
}

void Socket::bindWith(InetAddress & addr)
{
	int ret=bind(_fd,(struct sockaddr*)(addr.getInetAddressPtr()),sizeof(struct sockaddr));
	if(-1==ret)
	{
		perror("bind()");
		close(_fd);
		exit(-1);
	}
}

void Socket::listenTo(int num)
{
	int ret=listen(_fd,num);
	if(-1==ret)
	{
		perror("listen()");
		close(_fd);
		exit(-1);
	}
}
