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
	string source5=configure->getPathFor("source5");
	string source6=configure->getPathFor("source6");
	string source7=configure->getPathFor("source7");
	string dictionary=configure->getPathFor("dictionary");

	DictionaryMaker* dictionaryMaker=DictionaryMaker::getInstance();
	dictionaryMaker->addSourceIFrom(source1);
	dictionaryMaker->addSourceIFrom(source2);
	dictionaryMaker->addSourceIFrom(source3);
	dictionaryMaker->addSourceIFrom(source4);
	dictionaryMaker->addSourceIFrom(source5);
	dictionaryMaker->addSourceIFrom(source6);
	dictionaryMaker->addSourceXFrom(source7);
	dictionaryMaker->makeDictionary();
	dictionaryMaker->putDictionaryTo(dictionary);

	return 0;
}
