#ifndef SYMBOLS_H
#define SYMBOLS_H

typedef const unsigned char RAW_SYMBOL;
typedef const string& TYPE_LATERAL;
typedef const string& COMPARISION;
typedef const string& LOGIC;

// all struct symbols in here...
struct Symbols {
	// reserved names:
	TYPE_LATERAL INT = "int";
	TYPE_LATERAL STRING = "string";
	TYPE_LATERAL BOOL = "bool";
	TYPE_LATERAL POINT = "point";
	TYPE_LATERAL FLOAT = "float";
	TYPE_LATERAL LIST = "list";
	TYPE_LATERAL DICT = "dict";
	TYPE_LATERAL CONSTANT = "@CONSTANT";

	// operators:
	// arithmetic:
	RAW_SYMBOL MOD = '%'; // 37
	RAW_SYMBOL PLUS = '+'; // 43
	RAW_SYMBOL MINUS = '-'; // 45
	RAW_SYMBOL TIMES = '*'; // 42
	RAW_SYMBOL DIVIDE = '/'; // 47
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
	
};


#endif