#include "Configure.h"
#include "SplitTool.h"
#include "DictionaryMaker.h"


using std::string;

int main()
{
	string configPath="./Conf/DictionaryMaker.conf";
	Configure* configure=Configure::getInstance(configPath);
	string english=configure->getPathFor("english");
	string chinese=configure->getPathFor("chinese");
	string exclude=configure->getPathFor("exclude");
	string NLPIR=configure->getPathFor("NLPIR");
	string dictionary=configure->getPathFor("dictionary");
	
	SplitToolNLPIR splitToolNLPIR(NLPIR);
	DictionaryMaker* dictionaryMaker=DictionaryMaker::getInstance(&splitToolNLPIR);
	dictionaryMaker->addEnglishFrom(english);
//	dictionaryMaker->addChineseFrom(chinese);
	dictionaryMaker->addExcludeFrom(exclude);
	dictionaryMaker->makeDictionaryTo(dictionary);

	return 0;
}
