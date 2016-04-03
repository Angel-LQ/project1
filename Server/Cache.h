#ifndef _CACHE_
#define _CACHE_

#include "Correction.h"
#include <map>

using std::map;
using std::string;

class Cache
{
public:
	static Cache* getInstance(Correction &correction);
	string find(const string &word);
private:
	Cache(Correction &correction);
	~Cache();
	static Cache* _cache;
	Correction &_correction;
	map<string,string> _cache_map;   
	
	class Garbo
	{
	public:
		~Garbo();
	};
	static Garbo _garbo;
};

#endif
