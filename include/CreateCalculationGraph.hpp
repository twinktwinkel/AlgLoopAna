#ifndef CREATECALCULATIONGRAPH_HPP
#define CREATECALCULATIONGRAPH_HPP

#include "CalculationGraphDefs.hpp"
#include "StringOps.hpp"
#include <algorithm>

/** \brief Class to create a graph of a symbolic calculation 
 * 
 */
class CreateCalculationGraph
{
public:
	
	Expr * getCalcGraph(const std::string & in)
	{
		std::string str = removeCinS(in,' ');
		str = removeCinS(str,';');
		return interpret(str);
	}
	
	
private:
	

	struct OpFirst
	{
		std::string name;
		unsigned pos;
		int prio;
		int opSize;
		
		bool operator<(OpFirst const & in) const
		{	return prio < in.prio || (prio == in.prio && pos < in.pos);}
	};
	
	
	
	// k = r * m + k
	Expr * interpret(std::string const str, bool func = false)
	{
		Expr * res = new Expr();
		res->isFunction = false;
		res->isArray = false;
		res->isConstant = false;
		
		OpFirst of = getOpsOutofBrackets(str);
		if(of.opSize == 0) // is trivial expr or function/array call
		{
			if(getCharType(str[0])==CharType::BRACKET)
			{
				if(func)  // is Function or Array call
				{
					unsigned st = 1;
					for(unsigned i=1;i<str.size();++i)
						if(getCharType(str[i])==CharType::BRACKET || getCharType(str[i])==CharType::DELIMITER)
						{
							if(i-st>0)
								res->succ.push_back(interpret(str.substr(st,i-st)));
							st = ++i;
						}
						
					return res;
				}
				return interpret(str.substr(1,str.size()-2)); // is calc in brackets
			}
			
			for(unsigned i=0;i<str.size();++i)
			{
				if(getCharType(str[i])==CharType::BRACKET) // is function call or array access
				{
					res = interpret(str.substr(i,str.size()-i),true);
					res->name = str.substr(0,i);
					if(str[i] == '[')
						res->isArray = true;
					else
						res->isFunction = true;
					return res;
				}
			}
			// for trivial expr
			if(isNumeric(str))
				res->isConstant = true;
			else
				std::cout << str << " is not const\n";
			res->name = str;
			return res;
		}
		res->name = of.name;
		res->succ.push_back(interpret(str.substr(0,of.pos)));
		res->succ.push_back(interpret(str.substr(of.pos+of.opSize,str.size()-1-of.pos)));
		
		return res;
	}
	
	
	
	OpFirst getOpsOutofBrackets(std::string const & str)
	{
		OpFirst res,tmp;
		res.prio = 0;
		res.opSize = 0;
		CharType ct;
		unsigned bracketOpen = 0;
		for(unsigned i=0;i<str.size();++i)
		{
			ct = getCharType(str[i]);
			if(ct == CharType::BRACKET)
			{
				if(isOpenBracket(str[i]))
					++bracketOpen;
				else
					--bracketOpen;
			}
			if(bracketOpen == 0 && ct == CharType::OPERATOR && !(str[i] == '-' && str[i+1] == '>'))
			{
				tmp = getOpFirst(str.substr(i,2),i);
				if(tmp.opSize>1)
				{
					++i;
				}
				if(tmp.prio>res.prio)
					res = tmp;
			}
		}
		return res;
	}

	
	OpFirst getOpFirst(std::string const in, unsigned pos)
	{
		OpFirst res;
		res.pos = pos;
		res.opSize = 1;
		if(in.size()>1 && in[1]== '=')
		{
			res.name = in.substr(0,2);
			res.opSize = 2;
			res.prio = 4;
		}
		else
		{
			switch(in[0])
			{
				case('='):
					res.prio = 4;
					break;
				case('+'):
				case('-'):	
					res.prio = 3;
					break;
				case('*'):
				case('/'):	
					res.prio = 2;
					break;
				default:
					std::cout << "getOpFirst: No operator passed (arg=[" << in[0] << "]).\n";
					exit(1);
			}
			res.name = in[0];
		}
		return res;
	}
	
	
	bool hasOpInFront(std::string const & in, unsigned pos)
	{
		if(pos>0)
		{
			return getCharType(in[pos-1]) == CharType::OPERATOR;
		}
		return false;
	}
	
};

Expr * getCalcGraph(const std::string & in)
{
	CreateCalculationGraph ccg;
	return ccg.getCalcGraph(in);
}

#endif