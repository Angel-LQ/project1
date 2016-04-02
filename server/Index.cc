#include "Index.h"
#include "Dictionary.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::pair;
using std::string;
using std::ofstream;


Index* Index::getInstance(const Dictionary &diction)
{
	if(!_index)
		_index=new Index(diction);
	return _index;
}

void Index::addIndexFrom(const Dictionary &diction)
{
	auto &dict=diction._diction_vec;
	int i;
	for(i=0;i<dict.size();++i)
		for(auto it=dict[i].first.begin();it!=dict[i].first.end();++it)
			_idx_map[*it].insert(i);
}


Index::Index(const Dictionary &diction)
{
	set<int> idx;
	int i;
	for(i=0;i<26;++i)
		_idx_map.insert(pair<char,set<int>>('a'+i,idx));
	addIndexFrom(diction);
}

Index::~Index()
{
}

Index* Index::_index=NULL;

Index::Garbo::~Garbo()
{
	if(_index)
		delete _index;
}

Index::Garbo Index::_garbo;
