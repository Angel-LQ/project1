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

Socket* Socket::getInstance()
{
	if(!_socket)
		_socket=new Socket();
	return _socket;
}

Socket::Socket()
{
	_fd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==_fd)
	{
		perror("socket()");
	}
}

Socket::~Socket()
{
	close(_fd);
}

Socket* Socket::_socket=NULL;

void Socket::get(InetAddress & addr,int num)
{
	setReuseAddrIs(true);
	setReusePortIs(true);
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

Socket::Garbo::~Garbo()
{
	if(_socket)
		delete _socket;
}

Socket::Garbo Socket::_garbo;
