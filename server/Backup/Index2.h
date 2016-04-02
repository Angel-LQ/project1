#ifndef _INDEX2_
#define _INDEX2_

#include "Correction.h"
#include <map>
#include <set>

using std::map;
using std::set;
using std::string;

class Dictionary;

class Index
{
public:
	static Index* getInstance();
	void addIndexFrom(const Dictionary &diction);
	int putIndexTo(const string &path,char alpha);
	friend string correctBy(const Dictionary &diction,const Index &index,const string &word);
private:
	Index();
	~Index();
	static Index* _index;

	map<char,set<int>> _idx_map;

	map<string,int> _a_map;
	map<string,int> _b_map;
	map<string,int> _c_map;
	map<string,int> _d_map;
	map<string,int> _e_map;
	map<string,int> _f_map;
	map<string,int> _g_map;
	map<string,int> _h_map;
	map<string,int> _i_map;
	map<string,int> _j_map;
	map<string,int> _k_map;
	map<string,int> _l_map;
	map<string,int> _m_map;
	map<string,int> _n_map;
	map<string,int> _o_map;
	map<string,int> _p_map;
	map<string,int> _q_map;
	map<string,int> _r_map;
	map<string,int> _s_map;
	map<string,int> _t_map;
	map<string,int> _u_map;
	map<string,int> _v_map;
	map<string,int> _w_map;
	map<string,int> _x_map;
	map<string,int> _y_map;
	map<string,int> _z_map;

	class Garbo
	{
	public:
		~Garbo();
	};
	static Garbo _garbo;
};

#endif
