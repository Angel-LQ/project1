#include "Configure.h"
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>

using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::map;
using std::pair;

Configure* Configure::getInstance(const string &path)
{
	if(!_config)
		_config=new Configure(path);
	return _config;
}

string Configure::getPathFor(const string &name)
{
	auto it=_configure_map.find(name);
	if(_configure_map.end()==it)
	{
		perror("getPathFor()");
		return "";
	}
	return it->second;
}

Configure::Configure(const string &path)
{
	addConfigFrom(path);
}

Configure::~Configure()
{
}

Configure* Configure::_config=NULL;

int Configure::addConfigFrom(const string &path)
{
	ifstream ifs(path);
	if(!ifs.good())
	{	
		perror("addConfigFrom()");
		return -1;
	}
	string file;
	string addr;
	while(ifs>>file)
	{
		if(ifs>>addr)
			_configure_map.insert(pair<string,string>(file,addr));
	}
	ifs.close();
	return 0;
}

Configure::Garbo::~Garbo()
{
	if(_config)
		delete _config;
}

Configure::Garbo Configure::_garbo;
