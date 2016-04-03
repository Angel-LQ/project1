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

int Socket::connectTo(InetAddress &addr)
{
	connect(_fd,(struct sockaddr*)(addr.getInetAddressPtr()),sizeof(struct sockaddr));
	return _fd;
}

Socket::Garbo::~Garbo()
{
	if(_socket)
		delete _socket;
}

Socket::Garbo Socket::_garbo;
