#include "Dictionary.h"
#include <fstream>
#include <cstdlib>
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

string correction(string &word)
{
	for(int idx=0;idx<word.length();++idx)
	{
		if(!isalpha(word[idx]))
		{	
			word.clear();
			return word;
		}
		word[idx]=tolower(word[idx]);
	}
	return word;
}

Dictionary* Dictionary::getInstance()
{
	if(!_diction)
		_diction=new Dictionary();
	return _diction;
}

int Dictionary::addSourceNFrom(const string &sourceN)
{
	ifstream ifs(sourceN);
	if(!ifs.good())
	{
		cout<<"addSourceNFrom()"<<endl;
		return -1;
	}
	cout<<"addSourceN..."<<endl;
	string word;
	while(ifs>>word)
	{
		correction(word);
		if(word!="")
			++_sourceN_map[word];
	}
	ifs.close();
	return 0;
}

int Dictionary::addSourceXFrom(const string &SourceX)
{
	ifstream ifs(SourceX);
	if(!ifs.good())
	{
		cout<<"addSourceXFrom()"<<endl;
		return -1;
	}
	cout<<"addSourceX..."<<endl;
	string word;
	while(ifs>>word)
	{
		correction(word);
		if(word!="")
			_sourceX_set.insert(word);
	}
	ifs.close();
	return 0;
} 

void Dictionary::makeDictionary()
{
	cout<<"makeDictionary..."<<endl;
	for(auto it=_sourceN_map.begin();it!=_sourceN_map.end();++it)
	{
		if(_sourceX_set.end()==_sourceX_set.find(it->first))
			_diction_vec.push_back(*it);
	}
	_sourceN_map.clear();
	_sourceX_set.clear();
}

int Dictionary::putSourceNTo(const string &path)
{
	ofstream ofs(path);
	if(!ofs.good())
	{
		cout<<"putSourceNTo()"<<endl;
		return -1;
	}
	cout<<"putSourceN..."<<endl;
	for(auto it=_sourceN_map.begin();it!=_sourceN_map.end();++it)
		ofs<<it->first<<" "<<it->second<<endl;
	ofs.close();
	return 0;
}

int Dictionary::putSourceXTo(const string &path)
{
	ofstream ofs(path);
	if(!ofs.good())
	{
		cout<<"putSourceXTo()"<<endl;
		return -1;
	}
	cout<<"putSourceX..."<<endl;
	for(auto it=_sourceX_set.begin();it!=_sourceX_set.end();++it)
	{
		ofs<<*it<<endl;
	}
	ofs.close();
	return 0;
}

int Dictionary::putDictionaryTo(const string &path)
{
	ofstream ofs(path);
	if(!ofs.good())
	{
		cout<<"putDictionaryTo()"<<endl;
		return -1;
	}
	cout<<"putDictionary..."<<endl;
	for(auto it=_diction_vec.begin();it!=_diction_vec.end();++it)
		ofs<<it->first<<" "<<it->second<<endl;
	ofs.close();
	return 0;
}

Dictionary::Dictionary()
{
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
