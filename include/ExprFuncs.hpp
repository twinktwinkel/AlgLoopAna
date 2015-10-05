#ifndef EXPRFUNCS_HPP
#define EXPRFUNCS_HPP

// TODO write exp class with this funcs included and compare in time to this impl


bool isWriteOperator(const Expr * in)
{
	return in->name[0] == '=' || (in->name.size()>1 && in->name[1] == '=');
}

bool isVarWritten(Expr * writeOn, Expr * writes)
{
	bool res = isWriteOperator(writes) && *writeOn == *(writes->succ.front());
	if(res && (writeOn->isArray || writeOn->isFunction))
	{
		for(unsigned i=0;i<writes->succ.size();++i)
			if(!(*(writeOn->succ[i]) == *(writes->succ.front()->succ[i])))
				return false;
	}
	return res;
}

bool isArrayWritten(Expr * writeOn, Expr * writes)
{
	return isWriteOperator(writes) && *writeOn == *(writes->succ.front());
}

bool isExpRootInExpr(Expr * isIn, Expr * exp, bool depth = true)
{
	std::list<Expr *> queue;
	Expr * cur;
	queue.push_back(exp);
	while(!queue.empty())
	{
		cur = queue.front();
		queue.pop_front();
		if(*cur == *isIn)
			return true;
		for(Expr * e : cur->succ)
			if(depth)
				queue.push_front(e); // depth search
			else
				queue.push_back(e); // 
	}
	return false;
}

bool isExpInExpr(Expr * isIn, Expr * exp, bool depth = true)
{
	std::list<Expr *> queue;
	Expr * cur;
	queue.push_back(exp);
	while(!queue.empty())
	{
		cur = queue.front();
		queue.pop_front();
		if(*cur == *isIn)
		{
			bool flag = true;
			for(unsigned i=0;i<cur->succ.size();++i)
			{
				if(!isExpInExpr(isIn->succ[i],cur->succ[i],depth))
				{
					flag = false;
					break;
				}
			}
			if(flag)
				return true;
		}
		for(Expr * e : cur->succ)
			if(depth)
				queue.push_front(e); // depth search
			else
				queue.push_back(e); // 
	}
	return false;
}

bool isNameInExpr(std::string const isIn, Expr * exp, bool depth = true)
{
	std::list<Expr *> queue;
	Expr * cur;
	queue.push_back(exp);
	while(!queue.empty())
	{
		cur = queue.front();
		queue.pop_front();
		if(cur->name == isIn)
			return true;
		for(Expr * e : cur->succ)
			if(depth)
				queue.push_front(e); // depth search
			else
				queue.push_back(e); // 
	}
	return false;
}

Expr * getExprByName(std::string const isIn, Expr * exp, bool depth = true)
{
	std::list<Expr *> queue;
	Expr * cur;
	queue.push_back(exp);
	while(!queue.empty())
	{
		cur = queue.front();
		queue.pop_front();
		if(cur->name == isIn)
			return cur;
		for(Expr * e : cur->succ)
			if(depth)
				queue.push_front(e); // depth search
			else
				queue.push_back(e); // 
	}
	return NULL;
}



#endif