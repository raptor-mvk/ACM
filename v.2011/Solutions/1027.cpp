#pragma comment(linker, "/STACK:16777216")

#include <stdio.h>
#include <memory.h>

const int LT_COMMENT_BEGIN = 0;
const int LT_COMMENT_END = 1;
const int LT_MATH_BEGIN = 2;
const int LT_MATH_END = 3;
const int LT_MATH_SMB = 4;
const int LT_OTHER = 5;
const int LT_EOF = 6;
const int LT_COMMENT_TWICE = 7;
const int P_OK = 0;
const int P_ERROR = 1;

class Lexem_Analyser
{
private:
	char buffer;
public:
	Lexem_Analyser(): buffer(0) {}
	int get_lexem();
};

int Lexem_Analyser::get_lexem()
{
	char c;
	if (buffer)
	{
		c = buffer;
		buffer = 0;
	}
	else
		if (scanf("%c", &c) == EOF)
			return LT_EOF;
	if (c == '(')
	{
		if (scanf("%c", &c) == EOF)
			return LT_MATH_BEGIN;
		if (c == '*')
		{
			if (scanf("%c", &c) == EOF)
				return LT_COMMENT_BEGIN;
			if (c == ')')
				return LT_COMMENT_TWICE;
			buffer = c;
			return LT_COMMENT_BEGIN;
		}
		buffer = c;
		return LT_MATH_BEGIN;
	}
	if (c == '*')
	{
		if (scanf("%c", &c) == EOF)
			return LT_MATH_SMB;
		if (c == ')')
			return LT_COMMENT_END;
		buffer = c;
		return LT_MATH_SMB;
	}
	if (c == ')')
		return LT_MATH_END;
	if ((c >= '0') && (c <= '9') || (c == '+') || (c == '-') || (c == '/') || (c == '=') ||
		(c == '\r') || (c == '\n'))
		return LT_MATH_SMB;
	return LT_OTHER;
}

class Parser
{
private:
	int cur_lexem, inclusion_level;
	char in_math, in_comment;
public:
	Parser(): inclusion_level(0), in_comment(0) {}
	int parse(Lexem_Analyser *la);
};

int Parser::parse(Lexem_Analyser *la)
{
	int cur_lexem;
	cur_lexem = la->get_lexem();
	while (cur_lexem != LT_EOF)
	{
		if (in_comment)
		{
			if (cur_lexem == LT_COMMENT_END)
				in_comment = 0;
			if (cur_lexem == LT_COMMENT_TWICE)
				in_comment = 0;
		}
		else if (inclusion_level)
		{
			if (cur_lexem == LT_COMMENT_BEGIN)
				in_comment = 1;
			if (cur_lexem == LT_COMMENT_TWICE)
				in_comment = 1;
			if (cur_lexem == LT_COMMENT_END)
				inclusion_level--;
			if (cur_lexem == LT_MATH_BEGIN)
				inclusion_level++;
			if (cur_lexem == LT_MATH_END)
				inclusion_level--;
			if (cur_lexem == LT_OTHER)
				return P_ERROR;
		}
		else
		{
			if (cur_lexem == LT_COMMENT_BEGIN)
				in_comment = 1;
			if (cur_lexem == LT_COMMENT_TWICE)
				in_comment = 1;
			if (cur_lexem == LT_COMMENT_END)
				return P_ERROR;
			if (cur_lexem == LT_MATH_BEGIN)
				inclusion_level++;
			if (cur_lexem == LT_MATH_END)
				return P_ERROR;
		}
		cur_lexem = la->get_lexem();
	}
	if (in_comment || inclusion_level)
		return P_ERROR;
	return P_OK;
}

int main()
{
#ifndef ONLINE_JUDGE
   freopen("input.txt", "rt", stdin);
   freopen("output.txt", "wt", stdout);
#endif
	Lexem_Analyser *la;
	Parser *p;
	la = new Lexem_Analyser;
	p = new Parser;
	if (p->parse(la) == P_OK)
		printf("YES\n");
	else
		printf("NO\n");
}