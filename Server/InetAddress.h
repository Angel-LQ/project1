#ifndef _INETADDRESS_
#define _INETADDRESS_

#include <netinet/in.h>
#include <string>

using std::string; 

class InetAddress
{
public:
	InetAddress(unsigned short port);
	InetAddress(const char* ip,unsigned short port);
	InetAddress(const struct sockaddr_in &addr);

	struct sockaddr_in* getInetAddressPtr();
	string ip();
	unsigned short port();
private:
	struct sockaddr_in _addr;
};

#endif
