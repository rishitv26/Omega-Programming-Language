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

    cout << "READ INPUT -------------------------------" << endl;
    cout << code << endl;
    cout << "END OF RAW CODE --------------------------" << endl;

    struct Symbols symbols;

    // start by removing comments and blank lines:

    vector<string> lines = split_by(code, &symbols, symbols.END_LINE);
    vector<string> original_lines = lines; // used for error and comparison
    int counter = 0;
    lines.push_back(symbols.EXIT);
    while (!LEXER_SIMPLIFIED(&lines, &symbols)) LEXER_SIMPLIFY(&lines, &counter, &symbols);
    code = vect_to_str(lines, symbols.END_LINE);

    // then, replace all constants with thier laterals

    map <string, string> constants;
    vector<int> indexs;
    LEXER_FIND_CONSTANTS(&indexs, &lines, &symbols);
    LEXER_FILL_CONST_TABLE(&indexs, &lines, &constants, &original_lines, &symbols, file_name);
    for (auto elem : constants) {
        cout << "{ " << elem.first << ": " << elem.second << " }" << endl;
    }
    LEXER_REMOVE_LINES(&indexs, &lines);
    code = vect_to_str(lines, symbols.END_LINE); // update code
    LEXER_REPLACE_CONSTANTS(&constants, &lines, &code);
    // implement continue line behaviour:
    lines = split_by(code, &symbols, symbols.END_LINE, false, true);
    code = vect_to_str(lines, symbols.END_LINE);

    cout << "RESULT ----------------------" << endl << endl;
    cout << code;

    // preproccessor and simplification complete: start tokenising code ->
    ProgramTokens tokens(lines, &symbols); // <- tokenises code

    tokens.print_tokens();

    // compilation complete
    return 0;
}