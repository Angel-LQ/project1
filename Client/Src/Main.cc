#include "Configure.h"
#include "InetAddress.h"
#include "Socket.h"
#include "SocketIO.h"
#include "Epoll.h"
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <functional>

using std::cin;
using std::cout;
using std::endl;

int main()
{
	string configPath="../Conf/Client.conf";
	Configure* configure=Configure::getInstance(configPath);
	string ip=configure->getPathFor("ip");
	string port=configure->getPathFor("port");

//	InetAddress inetAddress(ip.c_str(),atoi(port.c_str()));
	InetAddress inetAddress(atoi(port.c_str()));
	Socket* socket=Socket::getInstance();
	int fd=socket->connectTo(inetAddress);
	SocketIO* socketIO=SocketIO::getInstance(fd);

//	Epoll* epoll=Epoll::getInstance(fd,*socketIO);

	cout<<"Welcome!"<<endl;

	string src,dest;
	while(true)
	{

		cin>>src;
		socketIO->writeString(src);
		socketIO->readString(dest);
		cout<<dest<<endl;

//		epoll->wait();
	}
	return 0;
}
