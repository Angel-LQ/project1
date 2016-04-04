#ifndef _SPLITTOOL_
#define _SOLITTOOL_

#include <iostream>
#include <vector>

using std::string;
using std::vector;

class SplitTool
{
public:
	SplitTool(){}
	virtual ~SplitTool(){}
	virtual vector<string> cut(const string &sentence)=0;
};

class SplitToolNLPIR:public SplitTool
{
public:
	SplitToolNLPIR(const string &path);
	~SplitToolNLPIR();
	vector<string> cut(const string &sentence);
};

#endif
