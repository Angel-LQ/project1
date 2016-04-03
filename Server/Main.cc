#include "Configure.h"
#include "Dictionary.h"
#include "Correction.h"
#include "Cache.h"
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
	string diction=configure->getPathFor("diction");
	string port=configure->getPathFor("port");
	string num=configure->getPathFor("num");

	Dictionary* dictionary=Dictionary::getInstance(diction);

	Correction* correction=Correction::getInstance(*dictionary);
	Cache* cache=Cache::getInstance(*correction);

	InetAddress inetAddress(atoi(port.c_str()));
	Socket* socket=Socket::getInstance();
	socket->get(inetAddress,atoi(num.c_str()));

	cout<<"Welcome!"<<endl;

	int fd=socket->acceptFor();
	SocketIO* socketIO=SocketIO::getInstance(fd);

	string src;
	string dest;
	while(true)
	{
		socketIO->readString(src);
		dest=cache->find(src);
		socketIO->writeString(dest);
	}

	return 0;
}
