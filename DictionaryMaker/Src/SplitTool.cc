#include "SplitTool.h"
#include <NLPIR.h>
#include <cstdio>
#include <sstream>

using std::istringstream;

SplitToolNLPIR::SplitToolNLPIR(const string &path)
{
	printf("%s\n",path.c_str());
	if(!NLPIR_Init(path.c_str(),UTF8_CODE))
		printf("NLPIR init failed!\n");
}

SplitToolNLPIR::~SplitToolNLPIR()
{
	NLPIR_Exit();
}

vector<string> SplitToolNLPIR::cut(const string &sentence)
{
	const char* sResult;
	sResult=NLPIR_ParagraphProcess(sentence.c_str(),0);
	string result(sResult);
	istringstream iss(result);
	string word;
	vector<string> words_vec;
	words_vec.reserve(1024);
	while(iss>>word)
		words_vec.push_back(word);
	return words_vec;
}
