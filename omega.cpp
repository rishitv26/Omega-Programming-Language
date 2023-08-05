#include "common.h"

// commandline compiler ->
int main() {
    const string file_name = "test.omega";

    // collect code from file:
    string code;
    fstream file(file_name);

    // load all code into 'code':
    stringstream buffer;
    buffer << file.rdbuf();
    code = buffer.str();
    file.close();

    // load symbol tables into a struct

    struct Symbols symbols;
    
    // start by removing comments and blank lines:

    vector<string> lines = split_by(code, &symbols, '\n');
    vector<string> original_lines = lines; // used for error and comparison
    int counter = 0;
    while (!LEXER_SIMPLIFIED(&lines, &symbols)) LEXER_SIMPLIFY(&lines, &counter, &symbols);
    code = vect_to_str(lines, '\n');
        
    // then, replace all constants with thier laterals

    map <string, string> constants;
    vector<int> indexs;
    LEXER_FIND_CONSTANTS(&indexs, &lines, &symbols);
    LEXER_FILL_CONST_TABLE(&indexs, &lines, &constants, &original_lines, &symbols, file_name);
    LEXER_REMOVE_LINES(&indexs, &lines);
    code = vect_to_str(lines, '\n'); // update code
    LEXER_REPLACE_CONSTANTS(&constants, &lines, &code);

    cout << code << endl;

    // preproccessor and simplification complete: start tokenising code ->

    // compilation complete
    return 0;
}