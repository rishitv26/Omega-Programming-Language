#include "common.h"

using std::cout;

const string Operation::get_symbol(bool raw)
{
    string ret = "";
    if (op1 != (char)0) {
        if (!raw) ret += op1;
        else if (op1 == '\n') ret += "\\n";
        else ret += op1;
    }
    else if (op2 != "") {
        if (!raw) return op2;
        else if (op1 == '\n') return "\\n";
        else return op2;
    }
    else _call_abort(__LINE__, __FILE__);
    return ret;
}

void _TOKEN_TYPE::set(void* I, ValidTokens t) { token_ptr = I; token_t = t; }

_TOKEN_TYPE::~_TOKEN_TYPE() {}

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
    const char not_allowed_in_front[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    const char not_allowed[] = ",./:'\\][-=+!@#$%^&*()~` \t'\"{};|";
    for (char i : not_allowed_in_front) {
        if (str[0] == i) return false;
    }
    for (int i = 0; i < (str.size() - 1); ++i) {
        for (char j : not_allowed) {
            if (str[i] == j) return false;
        }
    }

    return true;
}
#define isLiteral(x) isInt(x) || isPoint(x) || isDouble(x) || isList(x) || isDict(x) || isArray(x)
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
    }
    else if (
        isLiteral(str)
    ) {
        return ValidTokens::LITERAL;
    }
    else if (
        str == sym->WHILE ||
        str == sym->IF ||
        str == sym->RETURN ||
        str == sym->FOR ||
        str == sym->EXIT ||
        str == sym->TRUE ||
        str == sym->FALSE 
    ) {
        return ValidTokens::RESERVED;
    }
    return ValidTokens::IDENTIFIER;
}

#define APPEND_INS(x) struct _TOKEN_TYPE token; token.set((void*)x, t); Tokens.push_back(token)
/*
ProgramTokens::ProgramTokens(vector<string>& lines, struct Symbols* sym) // TODO: Debug this:
{
    cout << "TOKENIZING CODE -----------------------" << endl << endl;
    bool b = false;
    for (string l : lines) {
        string line = l + ' ';
        string temp2 = ""; // what previous word was
        string temp = ""; // current word
        bool toggle = false;
        bool reg = false;


        for (char i : line) {
            cout << i;
            // String literal checking...
            if (i == sym->STRING_DEF) {
                Register;
                if (toggle) { 
                    temp += i;
                    // add it as a literal:
                    struct Literal* ident = new Literal();
                    ident->name = temp;
                    CToken token;
                    token.set((void*)ident, ValidTokens::LITERAL);
                    Tokens.push_back(token);
                    toggle = false; 
                }
                else toggle = true;
            }
            if (toggle) {
                Register;
                temp += i;
                continue;
            }

            // Space checking...
            if (i == ' ' || i == '\t') { 
                if (!reg) temp2 = temp;
                temp = ""; 
                continue;
            }
            
            // Identifier checking:
            temp += i;
            string m = possibleMatchs(temp, sym); // look for possible token match's
            if ((temp.size() == 1 && temp2 != "") && isIdentifier(temp2) && (findTokenType(temp2, sym) == ValidTokens::IDENTIFIER)) {
                Register;
                // temp2 is an identifier:
                struct Identifier* ident = new Identifier(temp2);
                CToken token; 
                token.set((void*)ident, ValidTokens::IDENTIFIER);
                Tokens.push_back(token);
                
            }
            
            // ValidTokens checking...
            if (m != "") { // found one match:
                // find valid token for it:
                // All other detectory stuff, other than identifier...
                Register;
                ValidTokens t = findTokenType(m, sym);
                if (m == sym->EXIT) { 
                    struct Operation* op = new Operation();
                    if (m.size() == 1) op->op1 = m[0];
                    else op->op2 = m;
                    APPEND_INS(op);
                    b = true; break; 
                 }
                 if (t == ValidTokens::KEYWORD) {
                     struct Keyword* key = new Keyword(m);
                     APPEND_INS(key);
                 }
                 else if (t == ValidTokens::OPERATION) {
                     struct Operation* op = new Operation();
                     if (m.size() == 1) op->op1 = m[0];
                     else op->op2 = m;
                     APPEND_INS(op);
                 }
                 else if (t == ValidTokens::OTHERS) {
                     struct Others* other = new Others(m[0]);
                     APPEND_INS(other);
                 }
                 temp2 = temp;
                 temp = "";
                 reg = true;
            }

        }


        // check if there is identifiers and literals left:
        if (isIdentifier(temp2) && (findTokenType(temp2, sym) == ValidTokens::IDENTIFIER)) {
            // temp2 is an identifier:
            struct Identifier* ident = new Identifier(temp2);
            CToken token;
            token.set((void*)ident, ValidTokens::IDENTIFIER);
            Tokens.push_back(token);
        }
        
        // add a scentence ender...
        if (b) break;
        struct EndLine* end = new EndLine(sym->END_LINE);
        struct _TOKEN_TYPE token; 
        token.set((void*)end, ValidTokens::OTHERS);
        Tokens.push_back(token);

        cout << endl;
    }
    cout << endl;
}
*/
ProgramTokens::ProgramTokens(vector<string>& lines, struct Symbols* sym) {
    for (string line : lines) {
        string current_line = "";
        bool toggle = false;
        bool end = false;

        for (int i = 0; i < line.size(); ++i) {
            // cout << line[i];
            // string checking:
            if (line[i] == sym->STRING_DEF) {
                if (toggle) {
                    current_line += line[i];
                    // add it as a literal:
                    struct Literal* ident = new Literal();
                    ident->name = current_line;
                    ValidTokens t = ValidTokens::LITERAL;
                    APPEND_INS(ident);
                    toggle = false;
                    current_line = "";
                    continue;
                }
                else toggle = true;
            }
            if (toggle) { current_line += line[i]; continue; }

            if (line[i] == ' ' || line[i] == '\t') continue;
            current_line += line[i];
            vector<string> match = possibleMatchs(current_line, sym);

            if ((match.size() == 1) && isTokenMatchs(current_line, sym) != "") { // found exactly 1 match:
                string m = match[0];
                ValidTokens t = findTokenType(m, sym);
                if (m == sym->EXIT) {
                    struct Reserved* res = new Reserved(sym->EXIT);
                    APPEND_INS(res);
                    end = true; // and entire tokenization process
                    break; // end proccess
                }
                if (t == ValidTokens::KEYWORD) {
                    struct Keyword* key = new Keyword(m);
                    APPEND_INS(key);
                }
                else if (t == ValidTokens::OPERATION) {
                    struct Operation* op = new Operation();
                    if (m.size() == 1) op->op1 = m[0];
                    else op->op2 = m;
                    APPEND_INS(op);
                }
                else if (t == ValidTokens::OTHERS) {
                    struct Others* other = new Others(m[0]);
                    APPEND_INS(other);
                }
                else if (t == ValidTokens::RESERVED) {
                    struct Reserved* res = new Reserved(m);
                    APPEND_INS(res);
                }

                current_line = ""; // blank out for next word:
            }
            else if ((match.size() == 0) && isIdentifier(current_line)) { // nothing matched, maybe identifier or literal?
                const char not_allowed[] = ",./:'\\][-=+!@#$%^&*()~` \t'\"{};|";
                for (char j : not_allowed) {
                    if ((j == line[i + 1]) && isIdentifier(current_line)) {
                        // found an Identifier!
                        ValidTokens t = ValidTokens::IDENTIFIER;
                        struct Identifier* id = new Identifier(current_line);
                        APPEND_INS(id);
                        current_line = ""; // blank out
                        break;
                    }
                }
            }
        }
        // terminate comepletely if asked to do so
        if (end) break;
        // terminate scentence:
        struct Others* other = new Others(sym->END_LINE);
        ValidTokens t = ValidTokens::OTHERS;
        APPEND_INS(other);
        // cout << endl;
    }
}

ProgramTokens::~ProgramTokens() {}

vector<CToken>& ProgramTokens::return_tokens() { return Tokens; }

void ProgramTokens::print_tokens()
{
    for (CToken i : return_tokens()) {
        if (i.token_t == ValidTokens::IDENTIFIER) {
            struct Identifier id = *((struct Identifier*)i.token_ptr);
            cout << id.name << ' ' << "-> ";
        }
        else if (i.token_t == ValidTokens::KEYWORD) {
            struct Keyword id = *((struct Keyword*)i.token_ptr);
            cout << id.name << ' ' << "-> ";
        }
        else if (i.token_t == ValidTokens::LITERAL) {
            struct Literal id = *((struct Literal*)i.token_ptr);
            cout << id.name << ' ' << "-> ";
        }
        else if (i.token_t == ValidTokens::OPERATION) {
            struct Operation id = *((struct Operation*)i.token_ptr);
            cout << id.get_symbol(true) << ' ' << "-> ";
        }
        else if (i.token_t == ValidTokens::RESERVED) {
            struct Reserved id = *((struct Reserved*)i.token_ptr);
            cout << id.name << ' ' << "-> ";
        }
        else {
            struct Others id = *((struct Others*)i.token_ptr);
            cout << id.name << ' ' << "-> ";
        }
    }
    cout << endl;
}
