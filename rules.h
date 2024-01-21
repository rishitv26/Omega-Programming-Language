#ifndef RULES_H
#define RULES_H

#define MAX_EXPR_CHECK 100

// /E = expression; 
// /I = identifier;
// ... = expressions seperated with commas
// /P = list of parameters
// /T = datatype

const vector<string> RULESET[] = {
	// variables:
	{"/T", "/I", "\n"},
	{"/T", "/I", ":", "/E", "\n"},
	{"/T", "/I", ":", "[", "...", "]", "\n"},
	{"/T", "/I", "\n"},
	{"/T", "/I", ":", "<", "...", ">", "\n"},
	// new scope:
	{"{"},
	{"}"},
	// scope modifiers:
	{"/T", "/I", ":", "(", "/P", ")"},
	{"/T", "/I", ":"},
	{"if", "(", "/E", ")"},
	{"else"},
	{"elif", "(", "/E", ")"},
	{"while", "(", "/E", ")"},
	{"return", "/E"},
	// function calls:
	{"/T", "(", ")", "\n"},
	{"/T", "(", "...", ")", "\n"},
	// other:
	{"/E", "\n"},
};
const vector<string> UNARY_EXPR[] = {
	{"!", "/E"},
	{"#", "/E"},
	{"$", "/E"},
	{"-", "/E"},
};
const vector<string> BINARY_EXPR[] = {
	{"(", "/E", ")"},
	{"/E", ".", "/E"},
	{"/E", "+", "/E"},
	{"/E", "-", "/E"},
	{"/E", "*", "/E"},
	{"/E", "/", "/E"},
	{"/E", "%", "/E"},
	{"/E", "^", "/E"},
	{"/E", "==", "/E"},
	{"/E", "!=", "/E"},
	{"/E", ">=", "/E"},
	{"/E", "<=", "/E"},
	{"/E", "<", "/E"},
	{"/E", ">", "/E"},
	{"/E", "||", "/E"},
	{"/E", "&&", "/E"},
};

vector<string> reduceExpressions(ProgramTokens& tokens, int start, int end);
void interpretTokenSyntax(vector<string> list);

#endif