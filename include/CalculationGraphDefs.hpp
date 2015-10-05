#ifndef CALCULATIONGRAPHDEFS_HPP
#define CALCULATIONGRAPHDEFS_HPP

#include <utility>
#include <vector>
#include <list>

#include <iostream>
#include <string>

typedef std::pair<unsigned,unsigned> upair;

struct Expr
{
	std::string name;
	bool isConstant;
	bool isFunction;
	bool isArray;
	std::vector<Expr *> succ;
	
	bool operator==(Expr const & in) const
	{
		return name == in.name && succ.size() == succ.size();
	}
	
	bool operator<(Expr const & in) const
	{
		return name < in.name; 
	}
};



void getExprLevel(Expr const * in, std::vector<std::list<const Expr *> > & l, unsigned lvl = 0)
{
	if(lvl>=l.size())
	{
		l.push_back(std::list<const Expr *>());
	}
	l[lvl].push_back(in);
	for(const Expr * s : in->succ)
	{
		getExprLevel(s,l,lvl+1);
	}
}

void print(Expr const * g)
{
	std::vector<std::list<const Expr *> > level;
	getExprLevel(g,level);
	for(unsigned i=0;i<level.size();++i)
	{
		for(const Expr * n : level[i])
		{
			std::cout << "[" << n->name << "](" << n->succ.size() << ") ";
		}
		std::cout << "\n";
	}
}

struct CompExprRecEqual
{
	bool operator()(Expr const & l, Expr const & r) const
	{
		if(l == r)
		{			
			for(unsigned i=0;i<l.succ.size();++i)
				if(!(CompExprRecEqual::operator()(*l.succ[i],*r.succ[i]) 
				 || (l.succ[i]->isConstant && r.succ[i]->isConstant) || 
					(l.succ[i]->isConstant+l.succ[i]->isArray+l.succ[i]->isFunction == 0 
						&& r.succ[i]->isConstant+r.succ[i]->isArray+r.succ[i]->isFunction == 0)))
				{
					std::cout << l.succ[i]->name << "!=" << r.succ[i]->name << "\n";
					std::cout << "const:" << l.succ[i]->isConstant << "!=const" << r.succ[i]->isConstant << "\n";
					return false;
				}
			return true;
		}
		else
			return false;
	}
};

#endif