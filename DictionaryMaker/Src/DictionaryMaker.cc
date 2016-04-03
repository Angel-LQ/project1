#include "DictionaryMaker.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <cctype>
#include <string>
#include <cstdio>

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

DictionaryMaker* DictionaryMaker::getInstance()
{
	if(!_dictionaryMaker)
		_dictionaryMaker=new DictionaryMaker();
	return _dictionaryMaker;
}

int DictionaryMaker::addSourceIFrom(const string &sourceI)
{
	ifstream ifs(sourceI);
	if(!ifs.good())
	{
		perror("addSourceIFrom()");
		return -1;
	}
	cout<<"addSourceI..."<<endl;
	string word;
	while(ifs>>word)
	{
		correction(word);
		if(word!="")
			++_sourceI_map[word];
	}
	ifs.close();
	return 0;
}

int DictionaryMaker::addSourceXFrom(const string &SourceX)
{
	ifstream ifs(SourceX);
	if(!ifs.good())
	{
		perror("addSourceXFrom()");
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

void DictionaryMaker::makeDictionary()
{
	cout<<"makeDictionary..."<<endl;
	for(auto it=_sourceI_map.begin();it!=_sourceI_map.end();++it)
	{
		if(_sourceX_set.end()==_sourceX_set.find(it->first))
			_dictionary_vec.push_back(*it);
	}
	_sourceI_map.clear();
	_sourceX_set.clear();
}

int DictionaryMaker::putSourceITo(const string &path)
{
	ofstream ofs(path);
	if(!ofs.good())
	{
		perror("putSourceNTo()");
		return -1;
	}
	cout<<"putSourceN..."<<endl;
	for(auto it=_sourceI_map.begin();it!=_sourceI_map.end();++it)
		ofs<<it->first<<" "<<it->second<<endl;
	ofs.close();
	return 0;
}

int DictionaryMaker::putSourceXTo(const string &path)
{
	ofstream ofs(path);
	if(!ofs.good())
	{
		perror("putSourceXTo()");
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

int DictionaryMaker::putDictionaryTo(const string &path)
{
	ofstream ofs(path);
	if(!ofs.good())
	{
		perror("putDictionaryTo()");
		return -1;
	}
	cout<<"putDictionary..."<<endl;
	for(auto it=_dictionary_vec.begin();it!=_dictionary_vec.end();++it)
		ofs<<it->first<<" "<<it->second<<endl;
	ofs.close();
	return 0;
}

DictionaryMaker::DictionaryMaker()
{
}

DictionaryMaker::~DictionaryMaker()
{
}

DictionaryMaker* DictionaryMaker::_dictionaryMaker=NULL;

DictionaryMaker::Garbo::~Garbo()
{
	if(_dictionaryMaker)
		delete _dictionaryMaker;
}

DictionaryMaker::Garbo DictionaryMaker::_garbo;
