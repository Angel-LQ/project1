#ifndef _SOCKETIO_
#define _SOCKETIO_

#include <unistd.h>
#include <iostream>

using std::string;

class SocketIO
{
public:
	static SocketIO* getInstance(int fd);
	ssize_t readn(char* buff,size_t count);
	ssize_t writen(char* buff,size_t count);
	ssize_t readLine(char* buff,size_t max);
	void readString(string &word);
	void writeString(const string &word);
private:
	SocketIO(int fd);
	~SocketIO();
	static SocketIO* _socketIO;
	int _fd;
	ssize_t readPeek(char* buff,size_t max);

	class Garbo
	{
	public:
		~Garbo();
	};
	static Garbo _garbo;
};

#endif
