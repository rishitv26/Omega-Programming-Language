#include "common.h"

static bool find(string a, string b) {
	// match up first letters:
	bool bools = true;
	int size;
	if (a.size() >= b.size()) size = b.size();
	else size = a.size();

	for (int i = 0; i < size; ++i) {
		if (a[i] == b[i]) bools = bools && true;
		else bools = bools && false;
	}

	return bools;
}
vector<string> possibleMatchs(string in, Symbols* sym)
{
	// unsigned long long n = 18446744073709551615;
	vector<string> matchs;

	if (find(sym->INT, in)) matchs.push_back(sym->INT);
	if (find(sym->STRING, in)) matchs.push_back(sym->STRING);
	if (find(sym->BOOL, in)) matchs.push_back(sym->BOOL);
	if (find(sym->POINT, in)) matchs.push_back(sym->POINT);
	if (find(sym->DOUBLE, in)) matchs.push_back(sym->DOUBLE);
	if (find(sym->LIST, in)) matchs.push_back(sym->LIST);
	if (find(sym->ARRAY, in)) matchs.push_back(sym->ARRAY);
	// const is ignored since its preproccessor.
	if (find(sym->IS_EQUAL, in)) matchs.push_back(sym->IS_EQUAL);
	if (find(sym->NOT_EQUAL, in)) matchs.push_back(sym->NOT_EQUAL);
	if (find(sym->GREATER, in)) matchs.push_back(sym->GREATER);
	if (find(sym->GREATER_EQUAL, in)) matchs.push_back(sym->GREATER_EQUAL);
	if (find(sym->LESSER, in)) matchs.push_back(sym->LESSER);
	if (find(sym->LESSER_EQUAL, in)) matchs.push_back(sym->LESSER_EQUAL);
	if (find(sym->AND, in)) matchs.push_back(sym->AND);
	if (find(sym->OR, in)) matchs.push_back(sym->OR);
	if (find(sym->NOT, in)) matchs.push_back(sym->NOT);
	if (find(sym->WHILE, in)) matchs.push_back(sym->WHILE);
	if (find(sym->IF, in)) matchs.push_back(sym->IF);
	if (find(sym->RETURN, in)) matchs.push_back(sym->RETURN);
	if (find(sym->FOR, in)) matchs.push_back(sym->FOR);
	if (find(sym->EXIT, in)) matchs.push_back(sym->EXIT);
	if (find(sym->TRUE, in)) matchs.push_back(sym->TRUE);
	if (find(sym->FALSE, in)) matchs.push_back(sym->FALSE);
	if (find(sym->CLASS, in)) matchs.push_back(sym->CLASS);
	if (find(sym->VOID, in)) matchs.push_back(sym->VOID);
	if (find(sym->USE, in)) matchs.push_back(sym->USE);
	if (find(sym->AS, in)) matchs.push_back(sym->AS);
	
	// now check all chars:
	string temp;
	temp = ""; if (in[0] == sym->MOD) { temp += in[0]; matchs.push_back(temp); }
	temp = ""; if (in[0] == sym->PLUS) { temp += in[0]; matchs.push_back(temp); }
	temp = ""; if (in[0] == sym->MINUS) { temp += in[0]; matchs.push_back(temp); }
	temp = ""; if (in[0] == sym->TIMES) { temp += in[0]; matchs.push_back(temp); }
	temp = ""; if (in[0] == sym->DIVIDE) { temp += in[0]; matchs.push_back(temp); }
	temp = ""; if (in[0] == sym->RAISETO) { temp += in[0]; matchs.push_back(temp); }
	temp = ""; if (in[0] == sym->ASSIGN) { temp += in[0]; matchs.push_back(temp); }
	temp = ""; if (in[0] == sym->END_LINE) { temp += in[0]; matchs.push_back(temp); }
	temp = ""; if (in[0] == sym->START_ARG) { temp += in[0]; matchs.push_back(temp); }
	temp = ""; if (in[0] == sym->END_ARG) { temp += in[0]; matchs.push_back(temp); }
	temp = ""; if (in[0] == sym->DOT) { temp += in[0]; matchs.push_back(temp); }
	temp = ""; if (in[0] == sym->START_SCOPE) { temp += in[0]; matchs.push_back(temp); }
	temp = ""; if (in[0] == sym->END_SCOPE) { temp += in[0]; matchs.push_back(temp); }
	temp = ""; if (in[0] == sym->COMMA) { temp += in[0]; matchs.push_back(temp); }
	// comment line, continue, and preproc are skipped, since they are preproccessed.
	temp = ""; if (in[0] == sym->LOCATION) { temp += in[0]; matchs.push_back(temp); }
	temp = ""; if (in[0] == sym->POINTS) { temp += in[0]; matchs.push_back(temp); }
	temp = ""; if (in[0] == sym->START_INDEX) { temp += in[0]; matchs.push_back(temp); }
	temp = ""; if (in[0] == sym->END_INDEX) { temp += in[0]; matchs.push_back(temp); }


	return matchs;
}

#define find1(x, y) x == y
string isTokenMatchs(string in, vector<string> matchs)
{
	for (string& i : matchs) {
		if (in == i) return i;
	}

	return "";
}
