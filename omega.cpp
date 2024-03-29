#include "common.h"

// commandline compiler ->
int main() {
    const string file_name = "test.omg";
    // collect code from file:
    string code;
    fstream file(file_name);
    // load all code into 'code':
    stringstream buffer;
    buffer << file.rdbuf();
    code = buffer.str();
    file.close();
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
    vector <int> indexs;
    LEXER_FIND_CONSTANTS(&indexs, &lines, &symbols);
    LEXER_FILL_CONST_TABLE(&indexs, &lines, &constants, &original_lines, &symbols, file_name);
    LEXER_REMOVE_LINES(&indexs, &lines);
    code = vect_to_str(lines, symbols.END_LINE); // update code
    LEXER_REPLACE_CONSTANTS(&constants, &lines, &code);
    // implement continue line behaviour:
    lines = split_by(code, &symbols, symbols.END_LINE, false, true);
    code = vect_to_str(lines, symbols.END_LINE);

    // preproccessor and simplification complete: start tokenising code ->
    ProgramTokens tokens(lines, &symbols, original_lines); // <- tokenises code
    vector<string> reduced = reduceExpressions(tokens, 0, tokens.return_tokens().size() - 1);

    cout << "TOKENS: " << endl;
    tokens.print_tokens();

    // starting checks...
    interpretTokenSyntax(reduced);

    // compilation complete
    return 0;
}