#include "common.h"

vector<string> reduceExpressions(ProgramTokens& tokens, int start, int end)
{
	Symbols s;
	vector<string> list;
	for (int i = start; i < end + 1; ++i) list.push_back(tokens.atIndex(i));

	// reduce list:
	// standalone identifier simplifier:
	for (int i = 1; i < list.size() - 1; ++i) {
		vector<string> possibles = possibleMatchs(list[i], &s);
		string& current = list[i];
		string& before = list[i - 1];
		string& after = list[i + 1];
		if (list[i] == "\n");
		else if (isTokenMatchs(current, possibles) != "");
		else if (
			isIdentifier(current) && 
			(!isOperator(before)) &&
			(!isOperator(after))
		) current = "/I";
	}
	// 1 symbol simplfier
	for (int i = 0; i < list.size(); ++i) {
		if (list[i] == "/I") continue;
		vector<string> possibles = possibleMatchs(list[i], &s);
		if (isTokenMatchs(list[i], possibles) != "") continue;
		else if (isString(list[i])) list[i] = "/E";
		else if (isIdentifier(list[i])) list[i] = "/E";
        else if (isInt(list[i])) list[i] = "/E";
		else if (isLiteral(list[i])) list[i] = "/E";
	}
	// multi sybol simplifier
	for (int _ = 0; _ < MAX_EXPR_CHECK; ++_) {
		// 2 symbol simplfier:
		bool abs_break = false;
		if (list.size() > 1) for (int i = 0; i < list.size() - 1; ++i) {
			if (list[i] == "/I") continue;
			for (vector<string> u : UNARY_EXPR) {
				if (list.size() <= 1) { abs_break = true; break; }
				if (list[i] == u[0] && list[i + 1] == u[1]) {
					// found an expression:
					list.erase(list.begin() + i + 1);
					list[i] = "/E";
				}
			}
			if (abs_break) break;
		}
		// 3 symbol simplifier:
		abs_break = false;
		if (list.size() > 2) for (int i = 0; i < list.size() - 2; ++i) {
			if (list[i] == "/I") continue;
			for (vector<string> u : BINARY_EXPR) {
				if (list.size() <= 2) { abs_break = true; break; }
				if (list[i] == u[0] && list[i + 1] == u[1] && list[i + 2] == u[2]) {
					// found an expression:
					list.erase(list.begin() + i + 2);
					list.erase(list.begin() + i + 1);
					list[i] = "/E";
				}
			}
			if (abs_break) break;
		}

		if (list.size() == 1 && list[0] == "/E") {
			break;
		}
	}
	return list;
}
