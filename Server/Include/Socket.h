#ifndef _SOCKET_
#define _SOCKET_

class InetAddress;
class MutexLock;

class Socket
{
public:
	Socket();
	Socket(int fd);
	~Socket();
	void get(InetAddress &addr,int num);
	int acceptFor();
	int fd();
	void shutdownWrite();

	static InetAddress getLocalAddr(int fd);
	static InetAddress getPeerAddr(int fd);
private:
	int _fd;
	void setTcpNoDelayIs(bool flag);
	void setReuseAddrIs(bool flag);
	void setReusePortIs(bool flag);
	void setKeepAliveIs(bool flag);
	void bindWith(InetAddress & addr);
	void listenTo(int num);
};

#endif
