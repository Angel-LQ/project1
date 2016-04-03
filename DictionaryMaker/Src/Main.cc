#include "Configure.h"
#include "DictionaryMaker.h"

using std::string;

int main()
{
	string configPath="../Conf/DictionaryMaker.conf";
	Configure* configure=Configure::getInstance(configPath);
	string source1=configure->getPathFor("source1");
	string source2=configure->getPathFor("source2");
	string source3=configure->getPathFor("source3");
	string source4=configure->getPathFor("source4");
	string dictionary=configure->getPathFor("dictionary");

	DictionaryMaker* dictionaryMaker=DictionaryMaker::getInstance();
	dictionaryMaker->addSourceIFrom(source1);
	dictionaryMaker->addSourceIFrom(source2);
	dictionaryMaker->addSourceIFrom(source3);
	dictionaryMaker->addSourceXFrom(source4);
	dictionaryMaker->makeDictionary();
	dictionaryMaker->putDictionaryTo(dictionary);

	return 0;
}
