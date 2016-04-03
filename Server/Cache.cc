#include "Cache.h"
#include "cstdlib"
#include "Correction.h"
#include "iostream"

using std::cout;
using std::endl;

Cache* Cache::getInstance(Correction &correction)
{
	if(!_cache)
		_cache=new Cache(correction);
	return _cache;
}

string Cache::find(const string &word)
{
	auto it=_cache_map.find(word);
	if(it==_cache_map.end())
	{
		string retword=_correction.recommend(word);
		if(retword=="")
			retword=word;
		_cache_map.insert(pair<string,string>(word,retword));
		_cache_map.insert(pair<string,string>(retword,retword));
		return retword;
	}
	else
		return it->second;
}

Cache::Cache(Correction &correction)
:_correction(correction)
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
