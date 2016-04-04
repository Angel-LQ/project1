#ifndef _SOCKETIO_
#define _SOCKETIO_

#include "Noncopyable.h"
#include <unistd.h>
#include <iostream>

using std::string;

class SocketIO:private Noncopyable
{
public:
	SocketIO(int fd);
	ssize_t readn(char* buff,size_t count);
	ssize_t writen(char* buff,size_t count);
	ssize_t readLine(char* buff,size_t max);
	void readString(string &word);
	void writeString(const string &word);
private:
	ssize_t readPeek(char* buff,size_t max);
	int _fd;
};

#endif
