#include "common.h"

vector<string> split_by(string str, struct Symbols* sym, char by, bool simplify)
{
    vector<string> out;
    out.push_back(""); // initial item

    for (char i : str) {
        if (i == by) out.push_back("");
        else out.back() += i;
    }

    if (simplify) { // simfify for certain senarios:
        int counter = 0;
        while (!LEXER_SIMPLIFIED(&out, sym)) LEXER_SIMPLIFY(&out, &counter, sym);
    }

    return out;
}

static int find(string str, char c)
{
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == c) return i;
    }
    return -1;
}

string vect_to_str(vector<string> vect, char c) { // make all functions use sym->NEW_LINE instead of '\n'
    string out;

    for (const string& i : vect) {
        out += i + c;
    }

    return out;
}

bool LEXER_SIMPLIFIED(vector<string> *lines, struct Symbols* sym)
{
	for (const string& i : *lines) {
        if (find(i, sym->COMMENT) >= 0) return false;
        else if ( // register special line-to-line conditions here.
            i == "" ||
            i == " " ||
            i == "\t"
            ) return false;
	}

    return true;
}

void LEXER_SIMPLIFY(vector<string>* lines, int* counter, struct Symbols* sym)
{
    string l = (*lines)[*counter]; // string we care about (starts as first one)

    if (l[0] == ' ' || l[0] == '\t') {
        (*lines)[*counter].erase((*lines)[*counter].begin() + 0);
        return void(); // check this line again sometime.
    }
    // update l:
    l = (*lines)[*counter];

    if (find(l, sym->COMMENT) >= 0) { // if there is a comment:
        int comment_location = find(l, sym->COMMENT);
        (*lines)[*counter].erase(comment_location); // erase comment from that point
    }
    // update l:
    l = (*lines)[*counter];

    if (l == "" || l == "\t" || l == " ") // if it is a whitespace:
    {
        lines->erase((*lines).begin() + *counter);
    }
    else { // if current line is simplified, go to the next one.
        *counter += 1;
    }
    
}

void LEXER_FIND_CONSTANTS(vector<int>* indexs, vector<string>* lines, struct Symbols *sym)
{
    for (int i = 0; i < lines->size(); ++i) {
        string word = "";
        for (const char c : (*lines)[i]) {
            word += c;
            if (word == sym->CONSTANT) {
                // yay found constant line, slap this in indexs.
                indexs->push_back(i);
            }
            else if (word.size() == sym->CONSTANT.size()) break; // no point of checking farther
        }
    }
}

void LEXER_REMOVE_LINES(vector<int>* indexs, vector<string>* lines)
{
    for (int i : *indexs) {
        lines->erase(lines->begin() + i);
        for (int j = 0; j < indexs->size(); ++j) {
            if ((*indexs)[j] > i) { --(*indexs)[j]; }
        }
    }
}

void LEXER_FILL_CONST_TABLE(vector<int>* indexs, vector<string>* lines, map <string, string> *constants, vector<string>* original, struct Symbols* sym, string file)
{
    for (int i : *indexs) {
        vector<string> l = split_by((*lines)[i], sym, ' ', true);
        if (l.size() != 3) _call_compiler_error((*lines)[i], CONSTANT_DECLARATION_FORMAT, *original, file);
        // search for already used things:
        for (const auto& j : *constants) {
            if (j.first == l[1]) 
               _call_compiler_error((*lines)[i], CONSTANT_MULTIPLE_DEFINITIONS, *original, file);
        }
        (*constants)[l[1]] = l[2];
    }
}

void LEXER_REPLACE_CONSTANTS(map<string, string>* constants, vector<string>* lines, string* code)
{
    for (int i = 0; i < lines->size(); ++i) {
        for (const auto& constant : *constants) {
            while ((*lines)[i].find(constant.first) != 18446744073709551615) { // while its present
                if (constant.first.size() >= constant.second.size())
                    (*lines)[i].replace((*lines)[i].find(constant.first), constant.first.size(), constant.second);
                
                else if (constant.first.size() < constant.second.size())
                    (*lines)[i].replace((*lines)[i].find(constant.first), constant.second.size(), constant.second);
            }
        }
    }
    // when proccess is complete, modify 'code':
    *code = vect_to_str(*lines, '\n');
}
