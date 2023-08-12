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
    else _call_abort(__LINE__, __FILE__);
    return ret;
}

void _TOKEN_TYPE::set(void* I, ValidTokens t) { token_ptr = I; token_t = t; }

#define DESTROYER(x) delete (struct x*) token_ptr
_TOKEN_TYPE::~_TOKEN_TYPE()
{
    if         (token_t == ValidTokens::KEYWORD) DESTROYER(Keyword);
    else if    (token_t == ValidTokens::LITERAL) DESTROYER(Literal);
    else if    (token_t == ValidTokens::OPERATION) DESTROYER(Operation);
    else if    (token_t == ValidTokens::OTHERS) DESTROYER(Others);
    else if    (token_t == ValidTokens::IDENTIFIER) DESTROYER(Identifier);
        
    delete ptr_to_next_ins;
}

static bool isInt(string& in) {
    const char table[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

    for (char i : in) {
        for (char num : table) {
            if (i != num) return false;
        }
    }

    return true;
}
static bool isString(string& in) {
    struct Symbols s; // can be created here since it gets destroyed at end of function.
    if (in[0] != s.STRING_DEF || in[in.size() - 1] != s.STRING_DEF) return false;
    return true;
}
static bool isBool(string& in) {
    struct Symbols s;
    if (in == s.TRUE || in == s.FALSE) return true;
    return false;
}
static bool isPoint(string& in) {
    const char table[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'a', 'b', 'c', 'd'
    , 'e', 'f', 'A', 'B', 'C', 'D', 'E', 'F', 'x', 'X'};

    if (in[0] != '0' || (in[1] != 'x' || in[1] != 'X')) return false;
    if (count(in.begin(), in.end(), 'x') != 1) return false;
    for (char i : in) {
        for (char num : table) {
            if (i != num) return false;
        }
    }

    return true;
}
static bool isDouble(string& str) {
    const char table[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '.'};

    for (char i : str) {
        for (char num : table) {
            if (i != num) return false;
        }
    }

    return true;
}
static bool isList(string& str) {
    // no strict checking for now.
    if (str[0] != '[' || str[str.size() - 1] != ']') return false;
    return true;
}
static bool isDict(string& str) {
    // no strict checking for now:
    if (str[0] != '{' || str[str.size() - 1] != '}') return false;
    return true;
}
static bool isArray(string& str) {
    // no strict checking for now:
    if (str[0] != '<' || str[str.size() - 1] != '>') return false;
    return true;
}
static bool isIdentifier(string& str) {
    // again, not strict.
    // _ is allowed, special characters are not allowed.
    const char not_allowed_in_front[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '.', ','};
    const char not_allowed[] = ",./:'\\][-=+-!@#$%^&*()~";
    for (char i : not_allowed_in_front) {
        if (str[0] == i) return false;
    }
    for (char i : str) {
        for (char j : not_allowed) {
            if (i == j) return false;
        }
    }

    return true;
}
ValidTokens ProgramTokens::findTokenType(string str, struct Symbols *sym)
{
    if (
        str == sym->INT ||
        str == sym->STRING ||
        str == sym->BOOL ||
        str == sym->POINT ||
        str == sym->DOUBLE ||
        str == sym->LIST ||
        str == sym->ARRAY || 
        str == sym->CLASS
        // constant is skipped since it is preproccessed.

    ) { // if statement for Keyword
        return ValidTokens::KEYWORD;
    } else if (
        str[0] == sym->MOD ||
        str[0] == sym->PLUS ||
        str[0] == sym->MINUS ||
        str[0] == sym->TIMES ||
        str[0] == sym->DIVIDE ||
        str[0] == sym->RAISETO ||
        str[0] == sym->ASSIGN ||
        str[0] == sym->LOCATION ||
        str[0] == sym->POINTS ||
        str == sym->IS_EQUAL ||
        str == sym->NOT_EQUAL ||
        str == sym->GREATER ||
        str == sym->LESSER ||
        ((str == sym->LESSER_EQUAL) && !isArray(str)) ||
        ((str == sym->GREATER_EQUAL) && !isArray(str)) ||
        str == sym->AND ||
        str == sym->OR ||
        str == sym->NOT

    ) { // if statement for Operations
        return ValidTokens::OPERATION;
    } else if (
        str[0] == sym->END_LINE || 
        str[0] == sym->START_ARG ||
        str[0] == sym->END_ARG ||
        ((str[0] == sym->START_SCOPE) && !isDict(str)) ||
        ((str[0] == sym->END_SCOPE) && !isDict(str)) ||
        ((str[0] == sym->DOT) && !isDouble(str)) ||
        str[0] == sym->COMMA
    ) { // start of line operation:
        return ValidTokens::OTHERS;
    } else if (
        isInt(str) ||
        isString(str) ||
        isBool(str) ||
        isPoint(str) ||
        isDouble(str) ||
        isList(str) ||
        isDict(str) ||
        isArray(str)
    ) {
        return ValidTokens::LITERAL;
    }
    else if (isIdentifier(str)) {
        return ValidTokens::IDENTIFIER;
    }
}

#define APPEND_INS(x) struct _TOKEN_TYPE token; token.set((void*)x, t); Tokens.push_back(token)
ProgramTokens::ProgramTokens(vector<string>& lines, struct Symbols* sym)
{
    cout << "TOKENIZING CODE -----------------------" << endl << endl;
    for (string& line : lines) {
        string temp = "";
        for (char i : line) {
            cout << i;
            if (i == ' ' || i == '\t') continue;
            temp += i;
            vector<string> m = possibleMatchs(temp, sym); // look for possible token match's
            if (m.size() == 1 && temp == m[0]) { // found one match:
                // find valid token for it:
                ValidTokens t = findTokenType(m[0], sym);
                if (t == ValidTokens::KEYWORD) {
                    struct Keyword* key = new Keyword(m[0]);
                    APPEND_INS(key);
                }
                else if (t == ValidTokens::LITERAL) {
                    struct Literal* lit = new Literal();
                    lit->name = m[0];
                    APPEND_INS(lit);
                }
                else if (t == ValidTokens::OPERATION) {
                    struct Operation* op = new Operation();
                    if (m[0].size() == 1) op->op1 = m[0][0];
                    else op->op2 = m[0];
                    APPEND_INS(op);
                }
                else if (t == ValidTokens::OTHERS) {
                    struct Others* other = new Others(m[0][0]);
                    APPEND_INS(other);
                }
                else if (t == ValidTokens::IDENTIFIER) {
                    struct Identifier* ident = new Identifier(m[0]);
                    APPEND_INS(ident);
                };
                temp = "";
            }
        }
        // add a scentence terminator here...
        struct EndLine* end = new EndLine(sym->END_LINE);
        struct _TOKEN_TYPE token; 
        token.set((void*)end, ValidTokens::OTHERS);
        Tokens.push_back(token);
        // go to next line:
    }
}

ProgramTokens::~ProgramTokens()
{
    delete& Tokens;
}

vector<CToken>& ProgramTokens::return_tokens()
{
    return Tokens;
}
