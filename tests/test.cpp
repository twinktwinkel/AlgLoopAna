#include "CreateCalculationGraph.hpp"
#include "ProcessFile.hpp"
#include "ExprFuncs.hpp"
#include "VectorTest.hpp"

int main()
{
	ProcessFile pf("test.txt");
	std::vector<Expr *> exprs = pf.interpretFunction("add");
	for(unsigned i=0;i<exprs.size();++i)
	{
		std::cout << "_________________" << i << "__________________\n";
		print(exprs[i]);
	}
	std::cout << "##########################################\n";
	Expr * test = exprs[exprs.size()-2]->succ.back()->succ.front();
	std::cout << "test:\n";
	print(test);
	std::cout << "test has been written in:\n";
	print(exprs[exprs.size()-3]);
	std::cout << "? ==> ";
	if(isVarWritten(test,exprs[exprs.size()-3]))
		std::cout << "yes\n";
	else
		std::cout << "no\n";
	
	std::cout << "##########################################\n";
	std::cout << "test has been written in:\n";
	print(exprs[exprs.size()-4]);
	std::cout << "? ==> ";
	if(isVarWritten(test,exprs[exprs.size()-4]))
		std::cout << "yes\n";
	else
		std::cout << "no\n";
	
	
	std::list<std::list<Expr *> > equ = getEqExpr(exprs);
	for(auto lE : equ)
	{
		
		std::cout << "##########################################\n";
		std::cout << "\nEqu:\n";
		for(auto e : lE)
		{
			std::cout << "________________________\n";
			print(e);
			std::cout << "________________________\n";
		}
	}
	
	Expr * var = getExprByName("var2",exprs[0],true);
	if(var != NULL)
		std::cout << "var1 is: const:" << var->isConstant << " array:" << var->isArray << " func:" << var->isFunction << "\n";
	
	//for(unsigned i=0;i<256;++i)
	//	std::cout << i << " => " << (char)i << "\n";
	return 0;
}