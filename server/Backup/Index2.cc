#include "Index2.h"
#include "Dictionary.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::pair;
using std::string;
using std::ofstream;


Index* Index::getInstance()
{
	if(!_index)
		_index=new Index();
	return _index;
}

void Index::addIndexFrom(const Dictionary &diction)
{
	auto &dict=diction._diction_vec;
	int idx;
	for(idx=0;idx<dict.size();++idx)
	{
		for(auto it=dict[idx].first.begin();it!=dict[idx].first.end();++it)
		{
			switch (*it)
			{
				case 'a':
					_a_map.insert(pair<string,int>(dict[idx].first,idx));
					break;
				case 'b':
					_b_map.insert(pair<string,int>(dict[idx].first,idx));			
					break;
				case 'c':
					_c_map.insert(pair<string,int>(dict[idx].first,idx));
					break;
				case 'd':
					_a_map.insert(pair<string,int>(dict[idx].first,idx));
					break;
				case 'e':
					_e_map.insert(pair<string,int>(dict[idx].first,idx));
					break;
				case 'f':
					_g_map.insert(pair<string,int>(dict[idx].first,idx));
					break;
				case 'h':
					_h_map.insert(pair<string,int>(dict[idx].first,idx));
					break;
				case 'i':
					_i_map.insert(pair<string,int>(dict[idx].first,idx));
					break;
				case 'j':
					_j_map.insert(pair<string,int>(dict[idx].first,idx));
					break;
				case 'k':
					_k_map.insert(pair<string,int>(dict[idx].first,idx));
					break;
				case 'l':
					_l_map.insert(pair<string,int>(dict[idx].first,idx));
					break;
				case 'm':
					_m_map.insert(pair<string,int>(dict[idx].first,idx));
					break;
				case 'n':
					_n_map.insert(pair<string,int>(dict[idx].first,idx));
					break;
				case 'o':
					_o_map.insert(pair<string,int>(dict[idx].first,idx));
					break;
				case 'p':
					_p_map.insert(pair<string,int>(dict[idx].first,idx));
					break;
				case 'q':
					_q_map.insert(pair<string,int>(dict[idx].first,idx));
					break;
				case 'r':
					_r_map.insert(pair<string,int>(dict[idx].first,idx));
				case 's':
					_s_map.insert(pair<string,int>(dict[idx].first,idx));
					break;
				case 't':
					_t_map.insert(pair<string,int>(dict[idx].first,idx));
					break;
				case 'u':
					_u_map.insert(pair<string,int>(dict[idx].first,idx));
					break;
				case 'v':
					_v_map.insert(pair<string,int>(dict[idx].first,idx));
					break;
				case 'w':
					_w_map.insert(pair<string,int>(dict[idx].first,idx));
					break;
				case 'x':
					_x_map.insert(pair<string,int>(dict[idx].first,idx));
					break;
				case 'y':
					_y_map.insert(pair<string,int>(dict[idx].first,idx));
					break;
				case 'z':
					_z_map.insert(pair<string,int>(dict[idx].first,idx));
					break;			
				default : 
					break;
			}
		}
	}
}

int Index::putIndexTo(const string &path,char alpha)
{
	ofstream ofs(path);
	if(!ofs.good())
	{
		cout<<"putIndexTo()"<<endl;
		return -1;
	}
	switch (alpha)
	{
		case 'a':	
			cout<<"putIndexA..."<<endl;
			for(auto it=_a_map.begin();it!=_a_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 'b':	
			cout<<"putIndexB..."<<endl;
			for(auto it=_b_map.begin();it!=_b_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 'c':	
			cout<<"putIndexC..."<<endl;
			for(auto it=_c_map.begin();it!=_c_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 'd':	
			cout<<"putIndexD..."<<endl;
			for(auto it=_d_map.begin();it!=_d_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 'e':	
			cout<<"putIndexE..."<<endl;
			for(auto it=_e_map.begin();it!=_e_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 'f':	
			cout<<"putIndexF..."<<endl;
			for(auto it=_f_map.begin();it!=_f_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 'g':	
			cout<<"putIndexG..."<<endl;
			for(auto it=_g_map.begin();it!=_g_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 'h':	
			cout<<"putIndexH..."<<endl;
			for(auto it=_h_map.begin();it!=_h_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 'i':	
			cout<<"putIndexI..."<<endl;
			for(auto it=_i_map.begin();it!=_i_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 'j':	
			cout<<"putIndexJ..."<<endl;
			for(auto it=_j_map.begin();it!=_j_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 'k':	
			cout<<"putIndexK..."<<endl;
			for(auto it=_k_map.begin();it!=_k_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 'l':	
			cout<<"putIndexL..."<<endl;
			for(auto it=_l_map.begin();it!=_l_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 'm':	
			cout<<"putIndexM..."<<endl;
			for(auto it=_m_map.begin();it!=_m_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 'n':	
			cout<<"putIndexN..."<<endl;
			for(auto it=_n_map.begin();it!=_n_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 'o':	
			cout<<"putIndexO..."<<endl;
			for(auto it=_o_map.begin();it!=_o_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 'p':	
			cout<<"putIndexP..."<<endl;
			for(auto it=_p_map.begin();it!=_p_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 'q':	
			cout<<"putIndexQ..."<<endl;
			for(auto it=_q_map.begin();it!=_q_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 'r':	
			cout<<"putIndexR..."<<endl;
			for(auto it=_r_map.begin();it!=_r_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 's':	
			cout<<"putIndexS..."<<endl;
			for(auto it=_s_map.begin();it!=_s_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 't':	
			cout<<"putIndexT..."<<endl;
			for(auto it=_t_map.begin();it!=_t_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 'u':	
			cout<<"putIndexU..."<<endl;
			for(auto it=_u_map.begin();it!=_u_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 'v':	
			cout<<"putIndexV..."<<endl;
			for(auto it=_v_map.begin();it!=_v_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 'w':	
			cout<<"putIndexW..."<<endl;
			for(auto it=_w_map.begin();it!=_w_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 'x':	
			cout<<"putIndexX..."<<endl;
			for(auto it=_x_map.begin();it!=_x_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 'y':	
			cout<<"putIndexY..."<<endl;
			for(auto it=_y_map.begin();it!=_y_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		case 'z':	
			cout<<"putIndexZ..."<<endl;
			for(auto it=_z_map.begin();it!=_z_map.end();++it)
			ofs<<it->first<<" "<<it->second<<endl;
			break;
		default :
			cout<<"Wrong alpha"<<endl;
			break;
	}
	ofs.close();
	return 0; 
}

Index::Index()
{
}

Index::~Index()
{
}

Index* Index::_index=NULL;

Index::Garbo::~Garbo()
{
	if(_index)
		delete _index;
}

Index::Garbo Index::_garbo;
