#ifndef TOKENS_H
#define TOKENS_H // TODO

// tokens can be categorized into these structs:

enum class ValidTokens {
	IDENTIFIER = 0,
	KEYWORD = 1,
	LITERAL = 2,
	OPERATION = 3,
	OTHERS = 4,
};

struct Identifier {
	string name;
	TYPE_LATERAL type;
};

struct Keyword {
	TYPE_LATERAL name;
};

struct Literal {
	variant<int, string, double> value;
};

struct Operation {
	RAW_SYMBOL op1 = NULL;
	LOGIC op2 = "";
	COMPARISION op3 = "";
	const string get_symbol();
};

struct Others {
	const string val;
};

// fundamental type for every token:
typedef struct _TOKEN_TYPE {
	ValidTokens token_t;
	void* token_ptr = nullptr;

	void set(void* I, ValidTokens t);

} CToken;

// start tokenizing code:

class ProgramTokens {
private:
public:

};

#endif