#include "common.h"
#include "symbols.h"

vector<string>& possibleMatchs(string in, Symbols* sym)
{
	unsigned long long n = 18446744073709551615;
	vector<string> matchs;

	if (sym->INT.find(in) != n) matchs.push_back(sym->INT);
	if (sym->STRING.find(in) != n) matchs.push_back(sym->STRING);
	if (sym->BOOL.find(in) != n) matchs.push_back(sym->BOOL);
	if (sym->POINT.find(in) != n) matchs.push_back(sym->POINT);
	if (sym->DOUBLE.find(in) != n) matchs.push_back(sym->DOUBLE);
	if (sym->LIST.find(in) != n) matchs.push_back(sym->LIST);
	if (sym->DICT.find(in) != n) matchs.push_back(sym->DICT);
	if (sym->ARRAY.find(in) != n) matchs.push_back(sym->ARRAY);
	// const is ignored since its preproccessor.
	if (sym->IS_EQUAL.find(in) != n) matchs.push_back(sym->IS_EQUAL);
	if (sym->NOT_EQUAL.find(in) != n) matchs.push_back(sym->NOT_EQUAL);
	if (sym->GREATER.find(in) != n) matchs.push_back(sym->GREATER);
	if (sym->GREATER_EQUAL.find(in) != n) matchs.push_back(sym->GREATER_EQUAL);
	if (sym->LESSER.find(in) != n) matchs.push_back(sym->LESSER);
	if (sym->LESSER_EQUAL.find(in) != n) matchs.push_back(sym->LESSER_EQUAL);
	if (sym->AND.find(in) != n) matchs.push_back(sym->AND);
	if (sym->OR.find(in) != n) matchs.push_back(sym->OR);
	if (sym->NOT.find(in) != n) matchs.push_back(sym->NOT);
	if (sym->WHILE.find(in) != n) matchs.push_back(sym->WHILE);
	if (sym->IF.find(in) != n) matchs.push_back(sym->IF);
	if (sym->RETURN.find(in) != n) matchs.push_back(sym->RETURN);
	if (sym->FOR.find(in) != n) matchs.push_back(sym->FOR);
	if (sym->EXIT.find(in) != n) matchs.push_back(sym->EXIT);
	
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

	return matchs;
}
