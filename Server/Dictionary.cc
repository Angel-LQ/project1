#include "Dictionary.h"
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cctype>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::set;
using std::ifstream;
using std::ofstream;
using std::pair;

Dictionary* Dictionary::getInstance(const string &diction)
{
	if(!_diction)
		_diction=new Dictionary(diction);
	return _diction;
}

int Dictionary::loadDictionaryFrom(const string &diction)
{
	ifstream ifs(diction);
	if(!ifs.good())
	{
		perror("loadDictionaryFrom()");
		return -1;
	}
	cout<<"loadDictionaryFrom..."<<endl;
	string word;
	int freq;
	while(ifs>>word && ifs>>freq)
	{
		_diction_vec.push_back(pair<string,int>(word,freq));
	}
	ifs.close();
	return 0;
}

void Dictionary::generateIndex()
{
	set<int> idx;
	int i;
	for(i=0;i<26;++i)
		_index_map.insert(pair<char,set<int>>('a'+i,idx));
	for(i=0;i<_diction_vec.size();++i)
		for(auto it=_diction_vec[i].first.begin();it!=_diction_vec[i].first.end();++it)
			_index_map[*it].insert(i);
}

Dictionary::Dictionary(const string &diction)
{
	loadDictionaryFrom(diction);
	generateIndex();
}

Dictionary::~Dictionary()
{
}

Dictionary* Dictionary::_diction=NULL;

Dictionary::Garbo::~Garbo()
{
	if(_diction)
		delete _diction;
}

Dictionary::Garbo Dictionary::_garbo;
