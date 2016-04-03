#include "Configure.h"
#include "Dictionary.h"
#include "Cache.h"
#include "Task.h"
#include "InetAddress.h"
#include "Socket.h"
#include "SocketIO.h"
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

int main()
{
	string configPath="./Conf/Server.conf";
	Configure* configure=Configure::getInstance(configPath);
	string dictionaryPath=configure->getPathFor("dictionaryPath"); 
	string port=configure->getPathFor("port");
	string number=configure->getPathFor("number");

	Dictionary* dictionary=Dictionary::getInstance(dictionaryPath);
	Cache* cache=Cache::getInstance();
	Task task=Task(*dictionary,*cache);

	InetAddress inetAddress(atoi(port.c_str()));
	Socket* socket=Socket::getInstance();
	socket->get(inetAddress,atoi(number.c_str()));

	cout<<"Welcome!"<<endl;

	int fd=socket->acceptFor();
	SocketIO* socketIO=SocketIO::getInstance(fd);

	string src;
	string dest;
	while(true)
	{
		socketIO->readString(src);
		dest=cache->lookUp(src);
		dest=task.lookUp(src);
		socketIO->writeString(dest);
	}

	return 0;
}
