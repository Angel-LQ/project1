#ifndef _SOCKET_
#define _SOCKET_

class InetAddress;

class Socket
{
public:
	static Socket* getInstance();
	void get(InetAddress &addr,int num);
	int acceptFor();
private:
	Socket();
	~Socket();
	static Socket* _socket;
	int _fd;
	void setReuseAddrIs(bool flag);
	void setReusePortIs(bool flag);
	void bindWith(InetAddress & addr);
	void listenTo(int num);

	class Garbo
	{
	public:
		~Garbo();
	};
	static Garbo _garbo;
};

#endif
