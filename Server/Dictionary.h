#ifndef _DICTIONARY_
#define _DICTIONARY_

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
	static Dictionary* getInstance(const string &diction);
	friend Correction* Correction::getInstance(Dictionary &diction);
private:
	Dictionary(const string &diction);
	~Dictionary();
	int loadDictionaryFrom(const string &diction);
	void generateIndex();

	static Dictionary* _diction;
	vector<pair<string,int>> _diction_vec;
	map<char,set<int>> _index_map;

	class Garbo
	{
	public:
		~Garbo();
	};
	static Garbo _garbo;
};

#endif
