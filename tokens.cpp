#include "common.h"

const string Operation::get_symbol()
{
    string ret = "";
    if ((int)op1) {
        ret += op1;
        return ret;
    }
    else if (op2 != "") {
        return op2;
    }
    else if (op3 != "") {
        return op3;
    }
    else _call_abort(__LINE__, __FILE__);
    return ret;
}

void _TOKEN_TYPE::set(void* I, ValidTokens t) { token_ptr = I; token_t = t; }

ProgramTokens::ProgramTokens(vector<string>& lines, struct Symbols* sym)
{
    string temp;
    for (string& line : lines) {
        for (char i : line) {
            temp += i;
            vector<string> m = possibleMatchs(temp, sym); // look for possible token match's
            // TODO: comeplete algorithm to convert text to tokens.
        }
    }
}
