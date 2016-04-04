#include "SocketIO.h"
#include <cstdio>
#include <unistd.h>
#include <errno.h>
#include <cstring>
#include <string>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define BUFFSIZE 1024

SocketIO::SocketIO(int fd)
:_fd(fd)
{
}

ssize_t SocketIO::readn(char* buff,size_t count)
{
	size_t remain=count;
	char* pbuf=buff;
	ssize_t ret=0;
	while(remain)
	{
		ret=read(_fd,pbuf,remain);
		if(-1==ret)
		{
			if(errno==EINTR)
				continue;
			perror("read()");
			exit(-1);
		}
		else
			if(0==ret)
				break;
		pbuf=pbuf+ret;
		remain=remain-ret;
	}
	return count-remain;
} 

ssize_t SocketIO::writen(char* buff,size_t count)
{
	size_t remain=count;
	char* pbuf=buff;
	ssize_t ret=0;
	while(remain)
	{
		ret=write(_fd,pbuf,remain);
		if(-1==ret)
		{
			if(errno==EINTR)
				continue;
			perror("write()");
			exit(-1);
		}
		else
			if(0==ret)
				break;
		pbuf=pbuf+ret;
		remain=remain-ret;
	}
	return count-remain;
} 

ssize_t SocketIO::readLine(char* buff,size_t max)
{
	size_t remain=max-1;
	char* pbuf=buff;
	size_t total=0;
	ssize_t nread;
	int idx;
	int nsize;
	while(remain)
	{
		nread=readPeek(pbuf,remain);
		if(nread<=0)
			return nread;
		for(idx=0;idx!=nread;++idx)
		{
			if(pbuf[idx]=='\n')
			{
				nsize=idx+1;
				if(readn(pbuf,nsize)!=nsize)
					return -1;
				remain=remain-nsize;
				total=total+nsize;
				pbuf=pbuf+nsize;
				*pbuf='\0';
				return total;
			}
		}
		if(readn(pbuf,nread)!=nread)
			return -1;
		remain=remain-nread;
		pbuf=pbuf+nread;
		total=total+nread;
	}
	*pbuf='\0';
	return max-1;
}

void SocketIO::readString(string &word)
{
/*
	char buff[1024];
	memset(buff,0,sizeof(buff));
	readLine(buff,sizeof(buff));
	word=buff;
	int pos=word.find('\n');
	word=word.substr(0,pos);
*/
	char buff[BUFFSIZE];
	memset(buff,0,BUFFSIZE);
	readn(buff,BUFFSIZE);
	word=buff;
}	

void SocketIO::writeString(const string &word)
{
/*
	char buff[1024];
	memset(buff,0,sizeof(buff));
	strcpy(buff,word.c_str());
	char* pos=buff;
	while(*pos!='\0')
		++pos;
	*pos='\n';
	writen(buff,sizeof(buff));
*/
	char buff[BUFFSIZE];
	memset(buff,0,BUFFSIZE);
	strcpy(buff,word.c_str());
	writen(buff,BUFFSIZE);
}

ssize_t SocketIO::readPeek(char* buff,size_t count)
{
	ssize_t nread;
	do
	{
		nread=recv(_fd,buff,count,MSG_PEEK);
	}while(nread==-1 && errno==EINTR);
	return nread;
}
