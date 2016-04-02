#ifndef _INDEX_
#define _INDEX_

#include "Correction.h"
#include <map>
#include <set>

using std::map;
using std::set;
using std::string;

class Dictionary;

class Index
{
public:
	static Index* getInstance(const Dictionary &diction);
	void addIndexFrom(const Dictionary &diction);
	friend Correction* Correction::getInstance(Dictionary &diction,Index &index);
private:
	Index(const Dictionary &diction);
	~Index();
	static Index* _index;
	map<char,set<int>> _idx_map;

	class Garbo
	{
	public:
		~Garbo();
	};
	static Garbo _garbo;
};

#endif
