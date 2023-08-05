#ifndef SYMBOLS_H
#define SYMBOLS_H

typedef const unsigned char RAW_SYMBOL;
typedef const string& TYPE_LATERAL;
typedef const string& COMPARISION;
typedef const string& LOGIC;

// all struct symbols in here...
struct Symbols {
	// reserved names:
	TYPE_LATERAL INT = "int ";
	TYPE_LATERAL STRING = "string ";
	TYPE_LATERAL BOOL = "bool ";
	TYPE_LATERAL POINT = "point ";
	TYPE_LATERAL FLOAT = "float ";
	TYPE_LATERAL LIST = "list ";
	TYPE_LATERAL DICT = "dict ";
	TYPE_LATERAL ARRAY = "array ";
	TYPE_LATERAL CONSTANT = "@CONST ";

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

template <typename T, size_t S>
class Array { // array implementation into a class...
private:
	T c_array[S];
public:
	Array() {};
	~Array() { delete[] c_array; };
	constexpr size_t size() const { return S; };

	T& operator [](size_t n) {
		if (n + 1 > S) _call_abort(__LINE__, __FILE__);
		return c_array[n];
	};

	constexpr T* return_location() const { return c_array; }
};

template <typename F, typename S>
class Dictionary { // Dictonary implementation comeplete
private:
	map<F, S> cpp_dict;
public:
	Dictionary() {}
	~Dictionary() { delete cpp_dict; }
	size_t size() { return cpp_dict.size(); }

	S& get(F key) {
		return cpp_dict[key];
	};
};

class Pointer { // TODO....
private:
	variant<int, string, bool, float> c_ptr;
public:
	Pointer();
	~Pointer();
	void* raw_ptr();

	template <typename T>
	void point_to(T* obj) { c_ptr = (void*)obj; }

	template <typename T>
	T* cast_ptr() { return (T*)c_ptr; }
};

/*
class List {
private:
	vector<variant<>>

public:
	List();
	~List();
};
*/

#endif