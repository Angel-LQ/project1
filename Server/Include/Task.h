#ifndef _TASK_
#define _TASK_

#include <iostream>

using std::string;

class Dictionary;
class Cache;

class Task
{
public:
	Task(Dictionary &dictionary,Cache &cache);
	string lookUp(const string &word);
private:
	Dictionary &_dictionary;
	Cache &_cache;
};

#endif
