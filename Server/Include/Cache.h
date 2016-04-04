#ifndef _CACHE_
#define _CACHE_

#include <map>

using std::map;
using std::string;
using std::pair;

class MutexLock;

class Cache
{
public:
	static Cache* getInstance(MutexLock &mutexLock);
	string lookUp(const string &word);
	void add(const pair<string,string> &words);
private:
	Cache();
	~Cache();
	static Cache* _cache;

	map<string,string> _cache_map;   
	
	class Garbo
	{
	public:
		~Garbo();
	};
	static Garbo _garbo;
};

#endif
