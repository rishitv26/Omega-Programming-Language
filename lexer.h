#ifndef LEXER_H
#define LEXER_H

// helper functions:

vector <string> split_by(string str, char by = ' ');
string vect_to_str(vector<string> vect, char c);

// add a LEXER SIMPLIFY BOOLEAN to help simplify code
bool LEXER_SIMPLIFIED(vector<string>* lines);

// actually help simplify
void LEXER_SIMPLIFY(vector<string>* lines, int* counter);

// find all index's that have @CONSTANT
void LEXER_FIND_CONSTANTS(vector<int> *indexs, vector<string>* lines, struct Symbols* sym);

// remove all lines specified
void LEXER_REMOVE_LINES(vector<int>* indexs, vector<string>* lines);

// fill up table with all consts:
void LEXER_FILL_CONST_TABLE(vector<int>* indexs, vector<string>* lines, map <string, string> *constants);

// replace constant laterals:
void LEXER_REPLACE_CONSTANTS(map <string, string>* constants, vector<string>* lines);

#endif