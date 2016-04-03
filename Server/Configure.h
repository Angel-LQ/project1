#ifndef _CONFIGURE_
#define _CONFIGURE_

#include <map>

using std::map;
using std::string;

class Configure
{
public:
	static Configure* getInstance(const string &path);
	string getPathFor(const string &name);
private:
	Configure(const string &path);
	~Configure();
	static Configure* _config;
	map<string,string> _configure_map;
	int addConfigFrom(const string &path);

	class Garbo
	{
	public:
		~Garbo();
	};
	static Garbo _garbo;
};

#endif
