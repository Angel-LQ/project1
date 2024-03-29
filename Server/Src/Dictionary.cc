#include "Dictionary.h"
#include "MutexLock.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <queue>
#include <vector>
#include <functional>

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::set;
using std::ifstream;
using std::ofstream;
using std::pair;
using std::priority_queue;
using std::vector;
using std::size_t;

size_t nBytesCode(const char ch)
{
	size_t nBytes = 0;
	if(ch &(1 << 7))
	{
		if((ch & 0xF0) == 0xC0 || (ch & 0xF0) == 0xD0)  
		{												
			nBytes += 2;							
		}										
		else if((ch & 0xF0) == 0xE0)
		{
			nBytes += 3;
		}
		else if((ch & 0xF0) == 0xF0)
		{
			nBytes += 4;
		}
		else if((ch & 0xFF) == 0xF8)
		{
			nBytes += 5;
		}
		else if((ch & 0xFF) == 0xFE)
		{
			nBytes += 6;
		}
	}
	else
	{
		nBytes += 1;	
	}
	return nBytes;
}

size_t length(const string &str)
{
	size_t ilen = 0;
	for(std::size_t idx = 0; idx != str.size(); ++idx)
	{
		int nBytes = nBytesCode(str[idx]);
		idx += (nBytes - 1);
		++ilen;
	}
	return ilen;
}

int MinimumEditDistance(const string &dest,const string &src)
{
	int slen=src.length()+1;
	int dlen=dest.length()+1;
	int Edit[slen][dlen];
	int x,y;
	for(x=0;x<slen;++x)
		Edit[x][0]=x;
	for(y=1;y<dlen;++y)
		Edit[0][y]=y;
	for(x=1;x<slen;++x)
	{
		for(y=1;y<dlen;++y)
		{
			if(Edit[x-1][y-1]<Edit[x][y-1])
				Edit[x][y]=Edit[x-1][y-1];
			else
				Edit[x][y]=Edit[x][y-1];
			if(Edit[x][y]>Edit[x-1][y])
				Edit[x][y]=Edit[x-1][y];
			if(src[x-1]!=dest[y-1])
				++Edit[x][y];
		}
	}
	return Edit[slen-1][dlen-1];
}

Dictionary* Dictionary::getInstance(const string &dictionaryPath,MutexLock &mutexLock)
{
	if(!_dictionary)
	{
		MutexLockGuard mlg(mutexLock);
		if(!_dictionary)
			_dictionary=new Dictionary(dictionaryPath);
	}
	return _dictionary;
}

int Dictionary::loadDictionaryFrom(const string &dictionaryPath)
{
	ifstream ifs(dictionaryPath);
	if(!ifs.good())
	{
		perror("loadDictionaryFrom()");
		return -1;
	}
	cout<<"loadDictionaryFrom..."<<endl;
	string word;
	int freq;
	while(ifs>>word && ifs>>freq)
	{
		_dictionary_vec.push_back(pair<string,int>(word,freq));
	}
	ifs.close();
	return 0;
}

void Dictionary::generateIndex()
{
	set<int> idx;
	int i;
	for(i=0;i<26;++i)
		_index_map.insert(pair<char,set<int>>('a'+i,idx));
	for(i=0;i<_dictionary_vec.size();++i)
		for(auto it=_dictionary_vec[i].first.begin();it!=_dictionary_vec[i].first.end();++it)
			_index_map[*it].insert(i);
}

string Dictionary::lookUp(const string &word)
{
	set<int> totalIndex;
	int idx;
	int dist;
	priority_queue<Result,vector<Result>,Compare> que;
	for(idx=0;idx<word.length();++idx)
	{
		for(auto it=_index_map[word[idx]].begin();it!=_index_map[word[idx]].end();++it)
		{
			totalIndex.insert(*it);	
		}
	}
	for(auto it=totalIndex.begin();it!=totalIndex.end();++it)
	{
		dist=MinimumEditDistance(_dictionary_vec[*it].first,word);
		if(dist<2)
		{	
			Result res;
			res._word=_dictionary_vec[*it].first;
			res._freq=_dictionary_vec[*it].second;
			res._dist=dist;
			que.push(res);
		}
	}
	if(que.empty())
		return "";
	else
		return que.top()._word;
}

Dictionary::Dictionary(const string &diction)
{
	loadDictionaryFrom(diction);
	generateIndex();
}

Dictionary::~Dictionary()
{
}

Dictionary* Dictionary::_dictionary=NULL;

Dictionary::Garbo::~Garbo()
{
	if(_dictionary)
		delete _dictionary;
}

Dictionary::Garbo Dictionary::_garbo;
