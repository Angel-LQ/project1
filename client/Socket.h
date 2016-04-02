#ifndef _SOCKET_
#define _SOCKET_

class InetAddress;

class Socket
{
public:
	static Socket* getInstance();
	int connectTo(InetAddress &addr);
private:
	Socket();
	~Socket();
	static Socket* _socket;
	int _fd;

	class Garbo
	{
	public:
		~Garbo();
	};
	static Garbo _garbo;
};

#endif
