#include "TcpConnection.h"
#include <string.h>
#include <iostream>
#include <sstream>

using std::string;

const int BUFFSIZE=1024;

TcpConnection::TcpConnection(int fd)
: _socket(fd)
, _socketIO(fd)
, _localAddr(Socket::getLocalAddr(fd))
, _peerAddr(Socket::getPeerAddr(fd))
, _isShutdownWrite(false)
{
}

TcpConnection::~TcpConnection()
{
	if(!_isShutdownWrite)
	{
		shutdown();
	}
}

void TcpConnection::receive(string &msg)
{
	char buff[BUFFSIZE];
	memset(buff,0,sizeof(buff));
	_socketIO.readn(buff,BUFFSIZE);
	msg=buff;
}

void TcpConnection::send(const string &msg)
{
	char buff[BUFFSIZE];
	memset(buff,0,BUFFSIZE);
	strcpy(buff,msg.c_str());
	_socketIO.writen(buff,BUFFSIZE);
}

void TcpConnection::shutdown()
{
	if(!_isShutdownWrite) 
	{ _isShutdownWrite = true;
		_socket.shutdownWrite();
	}
}

string TcpConnection::connectionMsg() const
{
	std::ostringstream oss;
	oss<<_localAddr.ip()<<":"<<_localAddr.port()<< "--->"<<_peerAddr.ip() <<  ":" << _peerAddr.port()<< " ";
	return oss.str();
}


void TcpConnection::setConnectionCallback(TcpConnectionCallback cb)
{
	_onConnectionCb = cb;
}

void TcpConnection::setMessageCallback(TcpConnectionCallback cb)
{
	_onMessageCb = cb;
}

void TcpConnection::setCloseCallback(TcpConnectionCallback cb)
{
	_onCloseCb = cb;
}

void TcpConnection::handleConnectionCallback()
{
	if(_onConnectionCb)
		_onConnectionCb(shared_from_this());
}

void TcpConnection::handleMessageCallback()
{
	if(_onMessageCb)
		_onMessageCb(shared_from_this());
}

void TcpConnection::handleCloseCallback()
{
	if(_onCloseCb)
		_onCloseCb(shared_from_this());
}


