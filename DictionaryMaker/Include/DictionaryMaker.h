#ifndef _DICTIONARYMAKER_
#define _DICTIONARYMAKER_

#include <map>
#include <set>
#include <vector>

using std::string;
using std::map;
using std::set;
using std::vector;
using std::pair;

class DictionaryMaker
{
public:
	static DictionaryMaker* getInstance();
	int addSourceIFrom(const string &SourceI);
	int addSourceXFrom(const string &SourceX);
	void makeDictionary();
	int putSourceITo(const string &path);
	int putSourceXTo(const string &path);
	int putDictionaryTo(const string &path);
private:
	DictionaryMaker();
	~DictionaryMaker();
	static DictionaryMaker* _dictionaryMaker;
	map<string,int> _sourceI_map;
	set<string> _sourceX_set;
	vector<pair<string,int>> _dictionary_vec;

	class Garbo
	{
	public:
		~Garbo();
	};
	static Garbo _garbo;
};

#endif
