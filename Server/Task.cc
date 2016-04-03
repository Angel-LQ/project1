#include "Task.h"
#include "Dictionary.h"
#include "Cache.h"

Task::Task(Dictionary &dictionary,Cache &cache)
:_dictionary(dictionary)
,_cache(cache)
{
}

string Task::lookUp(const string &word)
{
	string result=_cache.lookUp(word);
	if(result=="")
	{
		result=_dictionary.lookUp(word);
		if(result=="")
			result=word;
		_cache.add(pair<string,string>(word,result));
		_cache.add(pair<string,string>(word,word));
	}
	return result;
}
