#include "Cache.h"
#include "MutexLock.h"
#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

Cache* Cache::getInstance(MutexLock &mutexLock)
{
	if(!_cache)
	{
		MutexLockGuard mlg(mutexLock);
		if(!_cache)
			_cache=new Cache();
	}
	return _cache;
}

string Cache::lookUp(const string &word)
{
	auto it=_cache_map.find(word);
	if(it==_cache_map.end())
		return "";
	else
		return it->second;
}

void Cache::add(const pair<string,string> &words)
{
	_cache_map.insert(words);
}

Cache::Cache()
{
}

Cache::~Cache()
{
}

Cache* Cache::_cache=NULL;

Cache::Garbo::~Garbo()
{
	if(_cache)
		delete _cache;
}

Cache::Garbo Cache::_garbo;
