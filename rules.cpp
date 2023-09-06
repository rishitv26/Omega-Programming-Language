#include "common.h"

RuleBody& RuleBody::get_next(int index)
{
	return *(next[index]);
}

void RuleBody::set_index(RuleBody* val, int index)
{
	next[index] = val;
}

string toString(char c) {
	return "" + c;
}

vector<RuleBody*> functions;
void initRules() {
	struct Symbols sym;
	// create and add rules here:
	// function definition:
	functions = {
		new RuleBody("IDENTIFIER", functions[1]),
		new RuleBody(toString(sym.START_ARG), functions[2], functions[5]),
		new RuleBody("KEYWORD", functions[3]),
		new RuleBody("IDENTIFIER", functions[4]),
		new RuleBody(toString(sym.COMMA), functions[5], functions[2]),
		new RuleBody(toString(sym.END_ARG), functions[6]),
		new RuleBody("ENDLINE", functions[7], functions[6]),
		new RuleBody(toString(sym.START_SCOPE), functions[8]),
		new RuleBody("STATEMENT", functions[8], functions[9]),
		new RuleBody(toString(sym.END_SCOPE)),
	};
	Rules["FUNCTIONS"] = functions;
	// statement definition: TODO

}

void endRules() {
	// delete all heap items of Rules.
}
