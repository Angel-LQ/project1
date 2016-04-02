#include "Configure.h"
#include "Dictionary.h"
#include "Index.h"
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
	string configPath="./Conf/main.conf";
	Configure* configure=Configure::getInstance(configPath);
	string source1=configure->getPathFor("source1");
	string source2=configure->getPathFor("source2");
	string source3=configure->getPathFor("source3");
	string source4=configure->getPathFor("source4");
	string diction=configure->getPathFor("diction");
	string port=configure->getPathFor("port");
	string num=configure->getPathFor("num");

	Dictionary* dictionary=Dictionary::getInstance();
	dictionary->addSourceNFrom(source1);
	dictionary->addSourceNFrom(source2);
	dictionary->addSourceNFrom(source3);
	dictionary->addSourceXFrom(source4);
	dictionary->makeDictionary();
	dictionary->putDictionaryTo(diction);

	Index* index=Index::getInstance(*dictionary);

	Correction* correction=Correction::getInstance(*dictionary,*index);
	Cache* cache=Cache::getInstance(*correction);

	InetAddress inetAddress(atoi(port.c_str()));
	Socket* socket=Socket::getInstance();
	socket->get(inetAddress,atoi(num.c_str()));
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
