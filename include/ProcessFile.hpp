#ifndef PROCESSFILE_HPP
#define PROCESSFILE_HPP

#include "CreateCalculationGraph.hpp"
#include <fstream>
#include <sstream>

class ProcessFile
{
public:
	ProcessFile(std::string const filename) : filename(filename), buffer_size(1024)
	{
		std::ifstream ins;
		ins.open(filename.c_str());
		if(!ins.good())
		{
			std::cout << "ProcessFile: Cannot open file.\n";
			exit(1);
		}
		ins.close();
	}
	
	
	std::vector<Expr *> interpretFunction(std::string const funcName) const
	{
		std::ifstream ins;
		std::list<std::string> strs;
		std::string str,tmp;
		std::string::size_type pos;
		char buffer[buffer_size];
		unsigned brackets;
		bool funcFound = false, skip = false;
		
		ins.open(filename.c_str());
		ins.getline(buffer,buffer_size);
		while(ins.good())
		{
			if(!skip)
				ins.getline(buffer,buffer_size);
			skip = false;
			str = buffer;
			if(funcFound)
			{
				if(str.find("{") != std::string::npos)
					++brackets;
				if(str.find("}") != std::string::npos)
				{
					--brackets;
					if(brackets == 0)
						ins.close();
				}
				std::string t = trimString(str);
				if(t.size()>0)
					strs.push_back(t);	
			}
			else 
			{
				tmp = "";
				pos = str.find(funcName);
				if(pos != std::string::npos)
				{
					bool flag = false;
					if(str.find("{") != std::string::npos)
						flag = true;
					else
					{
						ins.getline(buffer,buffer_size);
						tmp = buffer;
						if(tmp.find("{") != std::string::npos)
							flag = true;
						else 
						{
							skip = true;
							str = tmp;
						}
					}
					if(flag)
					{
						brackets = 1;
						funcFound = true;
					}
				}
			}
			
		}
		ins.close();
		std::vector<Expr *> res(strs.size());
		unsigned count = 0;
		CreateCalculationGraph ccg;
		for(std::string & s : strs)
		{
			res[count++] = ccg.getCalcGraph(s);
		}
		return res;
	}

private:
	std::string filename;
	const unsigned buffer_size;
	
	std::string trimString(std::string const & in) const
	{
		std::string res("");
		unsigned wordpos = isWordAtFirst(in);
		if(wordpos != 0)
		{
			if(isWordAtFirst(in.substr(wordpos,in.size()-wordpos)) != 0)
				res += in.substr(wordpos,in.size()-wordpos);
			else
				res += in;
		}
		res = removeCinS(res,' ');
		res = removeCinS(res,'	');
		return res;
	}
	
	unsigned isWordAtFirst(std::string const & in) const
	{
		bool foundSym = false;
		CharType ct;
		for(unsigned i=0;i<in.size();++i)
		{
			if(in[i] == ' ' || in[i] == '	')
				continue;
			ct = getCharType(in[i]);
			if((in [i] == '	' || in[i] == ' ' || in[i] == ';' || ct == CharType::OPERATOR) && foundSym)
				return i;
			if(ct == CharType::LETTER || ct == CharType::NUMBER || ct == CharType::SYMBOL)
			{
				foundSym = true;
			}
			else if(!foundSym)
				break;
		}
		return 0;
	}
};

#endif