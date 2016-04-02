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
using std::function;
using std::bind;

struct task
{
	void task1()
	{
		cout<<"1"<<endl;
	}	
	void task2()
	{
		cout<<"2"<<endl;
	}	

};

int main()
{
	string configPath="./Conf/main.conf";
	Configure* configure=Configure::getInstance(configPath);
	string ip=configure->getPathFor("ip");
	string port=configure->getPathFor("port");

//	InetAddress inetAddress(ip.c_str(),atoi(port.c_str()));
	InetAddress inetAddress(atoi(port.c_str()));
	Socket* socket=Socket::getInstance();
	int fd=socket->connectTo(inetAddress);
	SocketIO* socketIO=SocketIO::getInstance(fd);

	string src;
	string dest;
	
	task t;

	Epoll* epoll=Epoll::getInstance();
	epoll->addFd1(0,bind(&task::task1,&t));
	epoll->addFd2(fd,bind(&task::task2,&t));

	while(true)
	{
/*
		cin>>src;
		socketIO->writeString(src);
		socketIO->readString(dest);
		cout<<dest<<endl;
*/
		epoll->wait();
	}
	return 0;
}
