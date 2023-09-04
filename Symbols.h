#ifndef SYMBOLS_H
#define SYMBOLS_H

typedef const unsigned char RAW_SYMBOL;
typedef const string& TYPE_LATERAL;
typedef const string& COMPARISION;
typedef const string& LOGIC;
typedef const string& RESERVED;

// all struct symbols in here...
// add symbols by:
// adding it here
// adding in possibleMatchs & isTokenMatch
// adding in findTokenType
struct Symbols {
	// reserved names:
	TYPE_LATERAL INT = "int"; // done
	TYPE_LATERAL STRING = "string"; // done
	TYPE_LATERAL BOOL = "bool"; // done
	TYPE_LATERAL POINT = "point"; // done
	TYPE_LATERAL DOUBLE = "double"; // done
	TYPE_LATERAL LIST = "list"; // list is always [a, b, c, d]
	TYPE_LATERAL DICT = "dict"; // always d{p{a, b}, p{c, d}}
	TYPE_LATERAL ARRAY = "array"; // always <a, b, c, d>
	TYPE_LATERAL CLASS = "class"; // classes.
	TYPE_LATERAL CONSTANT = "@CONST "; // space at the end is important here...

	// operators:
	// arithmetic:
	RAW_SYMBOL MOD = '%'; // 37
	RAW_SYMBOL PLUS = '+'; // 43
	RAW_SYMBOL MINUS = '-'; // 45
	RAW_SYMBOL TIMES = '*'; // 42
	RAW_SYMBOL DIVIDE = '/'; // 47
	RAW_SYMBOL RAISETO = '^'; // 94
	// assignment:
	RAW_SYMBOL ASSIGN = ':'; // 58

	// punctuation:
	RAW_SYMBOL END_LINE = '\n'; // 10
	RAW_SYMBOL START_ARG = '('; // 40
	RAW_SYMBOL END_ARG = ')'; // 41
	RAW_SYMBOL START_SCOPE = '{'; // 123
	RAW_SYMBOL END_SCOPE = '}'; // 125
	RAW_SYMBOL DOT = '.'; // 46
	RAW_SYMBOL COMMA = ','; // 44
	RAW_SYMBOL COMMENT = ';'; // 59
	RAW_SYMBOL CONTINUE_LINE = '\\'; // 92
	RAW_SYMBOL STRING_DEF = '\"'; // 34

	// comparision:
	COMPARISION IS_EQUAL = "==";
	COMPARISION NOT_EQUAL = "!=";
	COMPARISION GREATER = ">";
	COMPARISION LESSER = "<";
	COMPARISION GREATER_EQUAL = ">=";
	COMPARISION LESSER_EQUAL = "<=";

	// before proccessing:
	RAW_SYMBOL PREPROC = '@'; // 64
	
	// pointer stuff:
	RAW_SYMBOL LOCATION = '#'; // 35
	RAW_SYMBOL POINTS = '$'; // 36

	// logic:
	LOGIC AND = "&&";
	LOGIC OR = "||";
	LOGIC NOT = "!";

	// reserved names:
	RESERVED WHILE = "while";
	RESERVED IF = "if";
	RESERVED RETURN = "return";
	RESERVED FOR = "for";
	RESERVED EXIT = "__exit";
	RESERVED TRUE = "true";
	RESERVED FALSE = "false";
	RESERVED VOID = "void";
};

// function to match givin symbol:
vector<string> possibleMatchs(string in, struct Symbols* sym);
string isTokenMatchs(string in, Symbols* sym);

#endif