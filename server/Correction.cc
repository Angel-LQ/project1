#include "Correction.h"
#include "Dictionary.h"
#include "Index.h"
#include <cstdlib>
#include <string>
#include <queue>
#include <vector>
#include <functional>

#include <iostream>

using std::endl;
using std::cout;

using std::priority_queue;
using std::vector;

int MinimumEditDistance(const string &dest,const string &src)
{
	int slen=src.length()+1;
	int dlen=dest.length()+1;
	int Edit[slen][dlen];
	int x,y;
	for(x=0;x<slen;++x)
		Edit[x][0]=x;
	for(y=1;y<dlen;++y)
		Edit[0][y]=y;
	for(x=1;x<slen;++x)
	{
		for(y=1;y<dlen;++y)
		{
			if(Edit[x-1][y-1]<Edit[x][y-1])
				Edit[x][y]=Edit[x-1][y-1];
			else
				Edit[x][y]=Edit[x][y-1];
			if(Edit[x][y]>Edit[x-1][y])
				Edit[x][y]=Edit[x-1][y];
			if(src[x-1]!=dest[y-1])
				++Edit[x][y];
		}
	}
	return Edit[slen-1][dlen-1];
}

string Correction::recommend(const string &word)
{
	set<int> totalIndex;
	int idx;
	int dist;
	priority_queue<Result,vector<Result>,Compare> que;
	for(idx=0;idx<word.length();++idx)
	{
		for(auto it=_index[word[idx]].begin();it!=_index[word[idx]].end();++it)
		{
			totalIndex.insert(*it);	
		}
	}
	for(auto it=totalIndex.begin();it!=totalIndex.end();++it)
	{
		dist=MinimumEditDistance(_diction[*it].first,word);
		if(dist<3)
		{	
			Result res;
			res._word=_diction[*it].first;
			res._freq=_diction[*it].second;
			res._dist=dist;
			que.push(res);
		}
	}
	if(que.empty())
		return "";
	else
		return que.top()._word;
}


Correction* Correction::getInstance(Dictionary &diction,Index &index)
{
	if(!_correction)
		_correction=new Correction(diction._diction_vec,index._idx_map);
	return _correction;
}

Correction::Correction(vector<pair<string,int> > &diction,map<char,set<int> > &index)
:_diction(diction)
,_index(index)
{
}

Correction::~Correction()
{
}

Correction* Correction::_correction=NULL;

Correction::Garbo::~Garbo()
{
	if(_correction)
		delete _correction;
}

Correction::Garbo Correction::_garbo;
