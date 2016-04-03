#ifndef _DICTIONARY_
#define _DICTIONARY_

#include <map>
#include <set>
#include <vector>

using std::string;
using std::map;
using std::set;
using std::vector;
using std::pair;

struct Result
{
	string _word;
	int _freq;
	int _dist;
};

struct Compare
{
	bool operator()(const Result &lhs,const Result &rhs)
	{
		if(lhs._dist>rhs._dist)
			return true;
		else
			if(lhs._dist==rhs._dist && lhs._freq>rhs._freq)
				return true;
			else
				if(lhs._dist==rhs._dist && lhs._freq==rhs._freq &&lhs._word>rhs._word)
					return true;
				else
					return false;
	}
};

class Dictionary
{
public:
	static Dictionary* getInstance(const string &dictionaryPath);
	string lookUp(const string &word);
private:
	Dictionary(const string &dictionaryPath);
	~Dictionary();
	int loadDictionaryFrom(const string &dictionaryPath);
	void generateIndex();

	static Dictionary* _dictionary;
	vector<pair<string,int>> _dictionary_vec;
	map<char,set<int>> _index_map;

	class Garbo
	{
	public:
		~Garbo();
	};
	static Garbo _garbo;
};

#endif
