#ifndef VECTORTEST_HPP
#define VECTORTEST_HPP

#include "CalculationGraphDefs.hpp"
#include "ExprFuncs.hpp"
#include <map>



std::list<std::list<Expr *> > getEqExpr(std::vector<Expr *> & in)
{
	std::list<std::list<Expr *> > res;
	std::vector<bool> grouped(in.size(),false);
	CompExprRecEqual comp;
	for(unsigned i=0;i<in.size();++i)
	{
		if(grouped[i])
			continue;
		
		for(unsigned j=i+1;j<in.size();++j)
		{
			if(comp(*in[i],*in[j]))
			{
				if(!grouped[i])
				{
					res.push_back(std::list<Expr *>());
					res.back().push_back(in[i]);
					grouped[i] = true;
				}
				res.back().push_back(in[j]);
				grouped[j] = true;
				
			}				
		}
	}
	return res;
}

Expr * translateToVector(std::list<Expr *> & in)
{
	return NULL;
}

#endif