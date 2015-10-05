	
	
	enum class CharType
	{
		NUMBER = 0, LETTER = 1, OPERATOR = 2, BRACKET = 3, SYMBOL = 4, ENDMARKER = 5, ERASABLE = 6, DELIMITER = 7
	};
	
	bool isOpenBracket(const char c)
	{	return c == '(' || c == '[';	}
	
	std::string removeCinS(std::string const & in, const char c)
	{
		std::string res("");
		for(unsigned i=0;i<in.size();++i)
			if(in[i]!=c)
				res += in[i];
		return res;
	}
	
	CharType getCharType(const char in)
	{
		if((int)in > 47 && (int)in < 58)
		{
			return CharType::NUMBER;
		}
		else if(((int)in > 64 && (int)in < 91) || ((int)in > 96 && (int)in < 123))
		{
			return CharType::LETTER;
		}
		else
		{
			switch(in) {
			case('+'):
			case('-'):
			case('='):
			case('*'):
			case('/'):
				return CharType::OPERATOR;
			case(','):
				return CharType::DELIMITER;
			case('('):
			case('['):
			case(')'):
			case(']'):
				return CharType::BRACKET;
			case(';'):
				return CharType::ENDMARKER;
			case('\n'):
				return CharType::ERASABLE;
			default:
				return CharType::SYMBOL;
			}
		}
	}
	
	bool isNumeric(std::string const & in)
	{
		for(unsigned i=0;i<in.size();++i)
			if(!(getCharType(in[i]) == CharType::NUMBER || in[i] == '.'))
			{
				return false;
			}
		return true;
	}	