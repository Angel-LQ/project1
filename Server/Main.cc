#include "MutexLock.h"
#include "Configure.h"
#include "Dictionary.h"
#include "Cache.h"
#include "Task.h"
#include "InetAddress.h"
#include "Socket.h"
#include "TcpConnection.h"
#include "EpollPoller.h"
#include <cstring>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <functional>

using std::cout;
using std::endl;
using std::string;
using std::function;
using std::bind;
using std::atoi;

void onConnection(TcpConnectionPtr conn)
{
	cout<<conn->connectionMsg()<<"has connected!"<<endl;
	conn->send("welcome to server.");
}

void onMessage(TcpConnectionPtr conn)
{
	string msg; 
	conn->receive(msg);
	conn->send(msg);
}

void onClose(TcpConnectionPtr conn)
{
	cout<<conn->connectionMsg()<<"has close."<<endl;
}

int main()
{
	MutexLock mutexLock;
	string configPath="./Conf/Server.conf";
	Configure* configure=Configure::getInstance(configPath,mutexLock);
	string dictionaryPath=configure->getPathFor("dictionaryPath"); 
	string port=configure->getPathFor("port");
	string number=configure->getPathFor("number");

	Dictionary* dictionary=Dictionary::getInstance(dictionaryPath,mutexLock);
	Cache* cache=Cache::getInstance(mutexLock);
	Task task=Task(*dictionary,*cache);

	InetAddress inetAddress(atoi(port.c_str()));
	Socket socket;
	socket.get(inetAddress,atoi(number.c_str()));
/*
	int peerfd=socket.acceptFor();
	TcpConnection tcpConnection(peerfd);
*/
	EpollPoller epollPoller(socket.fd());
	epollPoller.setConnectionCallback(onConnection);
	epollPoller.setMessageCallback(onMessage);
	epollPoller.setCloseCallback(onClose);

	epollPoller.loop();
/*
	cout<<"Welcome!"<<endl;

	string src;
	string dest;
	while(true)
	{
		tcpConnection.receive(src);
		dest=task.lookUp(src);
		tcpConnection.send(dest);
	}
*/
	return 0;
}
