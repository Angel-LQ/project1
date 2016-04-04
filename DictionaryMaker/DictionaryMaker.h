#ifndef _DICTIONARYMAKER_
#define _DICTIONARYMAKER_

#include <map>
#include <set>
#include <vector>

using std::string;
using std::map;
using std::set;
using std::vector;
using std::pair;

class SplitTool;

class DictionaryMaker
{
public:
	static DictionaryMaker* getInstance(SplitTool* splitTool);
	int addSourceEFrom(const string &SourceE);
	int addSourceCFrom(const string &SourceC);
	int addSourceXFrom(const string &SourceX);
	int addEnglishFrom(const string &dir);
	int addChineseFrom(const string &dir);
	int addExcludeFrom(const string &dir);
	int makeDictionaryTo(const string &path);
	int putDictionaryTo(const string &path);
private:
	DictionaryMaker(SplitTool* splitTool);
	~DictionaryMaker();
	static DictionaryMaker* _dictionaryMaker;
	map<string,int> _sourceE_map;
	map<string,int> _sourceC_map;
	set<string> _sourceX_set;
	vector<pair<string,int>> _dictionary_vec;
	
	SplitTool* _splitTool;

	class Garbo
	{
	public:
		~Garbo();
	};
	static Garbo _garbo;
};

#endif
