#include "common.h"

static int getIndex(vector<string>& v, string K)
{
	for (int i = 0; i < v.size(); ++i) {
		if (v[i].find(K) != 18446744073709551615) return i;
	}
	return -1;
}

void _call_compiler_error(const string line, unsigned int type, vector<string>& lines, const string file)
{
	cout << "Compiler Error C" << type << ": " << endl
		<< "\tFile <" << file << "> , line " << getIndex(lines, line) + 1 << endl
		<< endl << "-----> " << line << endl;
	
	switch (type)
	{
	case CONSTANT_DECLARATION_FORMAT:   
		cout << "\nConstant not defined properly.  " << endl; 
		break;
	case CONSTANT_MULTIPLE_DEFINITIONS: 
		cout << "\nConstant defined multiple times." << endl; 
		break;
	case INVALID_SYNTAX_TOKEN:
		cout << "\nInvalid syntax." << endl;
		break;

	default: break;
	}

	exit(1);
}
void _call_abort(unsigned int line, const char* file, string message)
{
	cout << endl;
	cout << " ----------------> ABORT!!! Called on " << line << " in " << file << endl;
	if (message != "") cout << ": " << message << endl;
	exit(1);
}
