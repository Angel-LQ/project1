#include "Task.h"
#include "Dictionary.h"
#include "Cache.h"

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

Task::Task(Dictionary &dictionary,Cache &cache)
:_dictionary(dictionary)
,_cache(cache)
{
}

string Task::lookUp(const string &word)
{
	string temp=word;
	correction(temp);
	string result=_cache.lookUp(temp);
	if(result=="")
	{
		result=_dictionary.lookUp(temp);
		if(result=="")
			result=temp;
		_cache.add(pair<string,string>(temp,result));
		_cache.add(pair<string,string>(temp,temp));
	}
	return result;
}
