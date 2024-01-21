#ifndef TOKENS_H
#define TOKENS_H // TODO

// tokens can be categorized into these structs:

enum class ValidTokens {
	IDENTIFIER = 0,
	KEYWORD = 1,
	LITERAL = 2,
	OPERATION = 3,
	OTHERS = 4,
	RESERVED = 5
};

struct Identifier {
	string name;
	Identifier(string n) :name(n) {};
};

struct Keyword {
	string name;
	Keyword(TYPE_LATERAL type) :name(type) {};
};

struct Literal {
	string name;
};

struct Operation {
	unsigned char op1 = (char)0;
	string op2 = "";
	const string get_symbol(bool raw = false);
};

struct Reserved {
	string name;
	Reserved(string n) :name(n) {}
};

struct Others {
	char name; 
	Others(RAW_SYMBOL sym) :name(sym) {};
};

#define isLiteral(x) isInt(x) || isPoint(x) || isDouble(x) || isList(x) || isArray(x)

// fundamental type for every token:
typedef struct _TOKEN_TYPE {
	int line_number = 0;
	
	ValidTokens token_t;
	void* token_ptr = nullptr;

	void set(void* I, ValidTokens t, int num);
	string get_raw_val();
	~_TOKEN_TYPE();
} CToken;

// start tokenizing code:
class ProgramTokens {
private:
	vector<CToken> Tokens;
	ValidTokens findTokenType(string str, struct Symbols *sym);

public:
	ProgramTokens(vector<string>& lines, struct Symbols* sym);
	~ProgramTokens();

	vector<CToken>& return_tokens();
	void print_tokens();
	string atIndex(int i);
};

bool isInt(string& in);
bool isString(string& in);
bool isOperator(string& s);
// done till here
bool isPoint(string& in);
bool isDouble(string& str);
bool isList(string& str);
bool isArray(string& str);
bool isIdentifier(string& str);

#endif