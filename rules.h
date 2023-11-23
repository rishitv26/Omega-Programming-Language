#ifndef RULES_H
#define RULES_H

// E = expression; # = identifier; I = integer; ... = expressions seperated with commas
const vector<string> RULESET[] = {
	// variables:
	{"int", "#"},
	{"int", "#", ":", "E"},
	{"string", "#"},
	{"string", "#", ":", "E"},
	{"bool", "#"},
	{"bool", "#", ":", "E"},
	{"point", "#"},
	{"point", "#", ":", "E"},
	{"double", "#"},
	{"double", "#", ":", "E"},
	{"double", "#", ":", "I", ".", "I"},
	{"list", "#"},
	{"list", "#", ":", "[", "...", "]"},
	{"array", "#"},
	{"array", "#", ":", "<", "...", ">"},
};
// #E = expression
const vector<string> UNARY_EXPR[] = {
	{"!", "#E"},
	{"#", "#E"},
	{"$", "#E"},
	{"-", "#E"},
};

bool isExpression(ProgramTokens& tokens, int start, int end);

#endif