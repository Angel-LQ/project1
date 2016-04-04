#include "DictionaryMaker.h"
#include "SplitTool.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <cctype>
#include <string>
#include <cstring>
#include <cstdio>
#include <dirent.h>

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::set;
using std::ifstream;
using std::ofstream;
using std::pair;

void getFilesFrom(const string &dir,vector<string> &Files)
{
	DIR *pDir=opendir(dir.c_str());
	if(!pDir)
	{
		perror("opendir()");
		return;
	}
	struct dirent *pEntry;
	while((pEntry=readdir(pDir)))
	{
		if(strcmp(pEntry->d_name,".")!=0 && strcmp(pEntry->d_name,"..")!=0)
		{	
			string file(pEntry->d_name);
			Files.push_back(file);
		}
	}
	closedir(pDir);
}

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

DictionaryMaker* DictionaryMaker::getInstance(SplitTool* splitTool)
{
	if(!_dictionaryMaker)
		_dictionaryMaker=new DictionaryMaker(splitTool);
	return _dictionaryMaker;
}

int DictionaryMaker::addSourceEFrom(const string &sourceE)
{
	ifstream ifs(sourceE);
	if(!ifs.good())
	{
		perror("addSourceEFrom()");
		return -1;
	}
	cout<<"addSourceE..."<<endl;
	string word;
	while(ifs>>word)
	{
		correction(word);
		if(word!="")
			++_sourceE_map[word];
	}
	ifs.close();
	return 0;
}

int DictionaryMaker::addSourceCFrom(const string &sourceC)
{
	ifstream ifs(sourceC);
	if(!ifs.good())
	{
		perror("addSourceCFrom()");
		return -1;
	}
	cout<<"addSourceC..."<<endl;
	ifs.seekg(0,ifs.end);
	int length=ifs.tellg();
	ifs.seekg(0,ifs.beg);
	
	vector<string> words_vec;
	string content;
	content.reserve(length);
	ifs.read(&*content.begin(),length);
	words_vec=_splitTool->cut(content);
	for(int idx=0;idx!=words_vec.size();++idx)
	{
		++_sourceC_map[words_vec[idx]];
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
		_sourceX_set.insert(word);
	}
	ifs.close();
	return 0;
} 

int DictionaryMaker::addEnglishFrom(const string &dir)
{
	vector<string> Files;
	getFilesFrom(dir,Files);
	for(auto it=Files.begin();it!=Files.end();++it)
	{
		addSourceEFrom(dir+(*it));
	}
}

int DictionaryMaker::addChineseFrom(const string &dir)
{
	vector<string> Files;
	getFilesFrom(dir,Files);
	for(auto it=Files.begin();it!=Files.end();++it)
	{
		addSourceCFrom(dir+(*it));
	}
}

int DictionaryMaker::addExcludeFrom(const string &dir)
{
	vector<string> Files;
	getFilesFrom(dir,Files);
	for(auto it=Files.begin();it!=Files.end();++it)
	{
		addSourceXFrom(dir+(*it));
	}
}

int DictionaryMaker::makeDictionaryTo(const string &path)
{
	cout<<"makeDictionary..."<<endl;
	for(auto it=_sourceE_map.begin();it!=_sourceE_map.end();++it)
	{
		if(_sourceX_set.end()==_sourceX_set.find(it->first))
			_dictionary_vec.push_back(*it);
	}
	for(auto it=_sourceC_map.begin();it!=_sourceC_map.end();++it)
	{
		if(_sourceX_set.end()==_sourceX_set.find(it->first))
			_dictionary_vec.push_back(*it);
	}
	return putDictionaryTo(path);
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

DictionaryMaker::DictionaryMaker(SplitTool *splitTool)
:_splitTool(splitTool)
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
