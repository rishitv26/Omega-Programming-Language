#include "common.h"

// commandline compiler ->
int main() {
    
    // collect code from file:
    string code;
    fstream file("test.omega");

    // load all code into 'code':
    stringstream buffer;
    buffer << file.rdbuf();
    code = buffer.str();

    // load symbol tables into a struct

    struct Symbols symbols;
    
    // start by removing comments and blank lines:

    vector<string> lines = split_by(code, '\n');
    int counter = 0;
    while (!LEXER_SIMPLIFIED(&lines)) LEXER_SIMPLIFY(&lines, &counter);
    code = vect_to_str(lines, '\n');
        
    // then, replace all constants with thier laterals

    map <string, string> constants;
    vector<int> indexs;
    LEXER_FIND_CONSTANTS(&indexs, &lines, &symbols);
    LEXER_FILL_CONST_TABLE(&indexs, &lines, &constants);
    LEXER_REMOVE_LINES(&indexs, &lines);
    code = vect_to_str(lines, '\n'); // update code
    LEXER_REPLACE_CONSTANTS(&constants, &lines);

    cout << code << endl;

    // compilation complete
    file.close();
    return 0;
}