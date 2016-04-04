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
using std::ref;

void onConnection(TcpConnectionPtr conn)
{
	cout<<conn->connectionMsg()<<"has connected!"<<endl;
	conn->send("welcome to server.");
}

void onMessages(TcpConnectionPtr conn,Task &task)
{
	string src;
	string dest; 
	conn->receive(src);
	dest=task.lookUp(src);
	conn->send(dest);
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

	function<void(TcpConnectionPtr)> onMessage=bind(onMessages,std::placeholders::_1,task);

	EpollPoller epollPoller(socket.fd());
	epollPoller.setConnectionCallback(onConnection);
	epollPoller.setMessageCallback(onMessage);
	epollPoller.setCloseCallback(onClose);

	epollPoller.loop();

	return 0;
}
