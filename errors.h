#ifndef ERRORS_H
#define ERRORS_H

constexpr enum COMPILER_ERRORS {
	CONSTANT_DECLARATION_FORMAT = 300,
	CONSTANT_MULTIPLE_DEFINITIONS = 301,
	CONSTANT_MIRROR_DEFINITIONS = 302,
	INVALID_SYNTAX_TOKEN = 303,
};

void _call_compiler_error(const string line, unsigned int type, vector<string>& lines, const string file);
void _call_abort(unsigned int line, const char* file, string message = "");

#endif