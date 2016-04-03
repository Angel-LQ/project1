#ifndef _CORRECTION_
#define _CORRECTION_

#include <vector>
#include <map>
#include <set>

using std::vector;
using std::pair;
using std::string;
using std::map;
using std::set;

class Dictionary;

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

class Correction
{
public:
	static Correction* getInstance(Dictionary &diction);
	string recommend(const string &word);
private:
	Correction(vector<pair<string,int>> &diction,map<char,set<int>> &index);
	~Correction();
	static Correction* _correction;

	vector<pair<string,int>> &_diction;
	map<char,set<int>> & _index;

	class Garbo
	{
	public:
		~Garbo();
	};
	static Garbo _garbo;
};

#endif
