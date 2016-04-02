#ifndef _DICTIONARY_
#define _DICTIONARY_

#include "Index.h"
#include "Correction.h"
#include <map>
#include <set>
#include <vector>

using std::string;
using std::map;
using std::set;
using std::vector;
using std::pair;

class Dictionary
{
public:
	static Dictionary* getInstance();
	int addSourceNFrom(const string &SourceN);
	int addSourceXFrom(const string &SourceX);
	void makeDictionary();
	int putSourceNTo(const string &path);
	int putSourceXTo(const string &path);
	int putDictionaryTo(const string &path);
	friend void Index::addIndexFrom(const Dictionary &diction);
	friend Correction* Correction::getInstance(Dictionary &diction,Index &index);
private:
	Dictionary();
	~Dictionary();
	static Dictionary* _diction;
	map<string,int> _sourceN_map;
	set<string> _sourceX_set;
	vector<pair<string,int>> _diction_vec;

	class Garbo
	{
	public:
		~Garbo();
	};
	static Garbo _garbo;
};

#endif
