#ifndef ERRORS_H
#define ERRORS_H

constexpr auto CONSTANT_DECLARATION_FORMAT = 300;
constexpr auto CONSTANT_MULTIPLE_DEFINITIONS = 301;

void _call_compiler_error(const string line, unsigned int type, vector<string>& lines, const string file);

#endif