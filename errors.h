#ifndef ERRORS_H
#define ERRORS_H

constexpr unsigned int CONSTANT_DECLARATION_FORMAT = 300;
constexpr unsigned int CONSTANT_MULTIPLE_DEFINITIONS = 301;
constexpr unsigned int CONSTANT_MIRROR_DEFINITIONS = 302;

void _call_compiler_error(const string line, unsigned int type, vector<string>& lines, const string file);
void _call_abort(unsigned int line, const char* file, string message = "");

#endif