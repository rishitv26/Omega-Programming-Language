#ifndef RULES_H
#define RULES_H

#define MAX_EXPR_CHECK 100

// /E = expression; /I = identifier; /Int = integer; ... = expressions seperated with commas
const vector<string> RULESET[] = {
	// variables:
	{"int", "/I"},
	{"int", "/I", ":", "/E"},
	{"string", "/I"},
	{"string", "/I", ":", "/E"},
	{"bool", "/I"},
	{"bool", "/I", ":", "/E"},
	{"point", "/I"},
	{"point", "/I", ":", "/E"},
	{"double", "/I"},
	{"double", "/I", ":", "/E"},
	{"list", "/I"},
	{"list", "/I", ":", "[", "...", "]"},
	{"array", "/I"},
	{"array", "/I", ":", "<", "...", ">"},
};
// #E = expression
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

#endif