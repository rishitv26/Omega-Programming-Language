#include "common.h"

bool isExpression(ProgramTokens& tokens, int start, int end)
{
	bool expr = false;
	vector<string> list;
	for (int i = start; i < end + 1; ++i) list.push_back(tokens.atIndex(i));

	// reduce list:
	// 1 symbol simplfier
	for (int i = 0; i < list.size(); ++i) {
		if (isIdentifier(list[i])) list[i] = "#E";
        else if (isInt(list[i])) list[i] = "#E";
		else if (isLiteral(list[i])) list[i] = "#E";
	}

	for (int _ = 0; _ < MAX_EXPR_CHECK; ++_) {
		// 2 symbol simplfier:
		bool abs_break = false;
		if (list.size() > 1) for (int i = 0; i < list.size() - 1; ++i) {
			for (vector<string> u : UNARY_EXPR) {
				if (list.size() <= 1) { abs_break = true; break; }
				if (list[i] == u[0] && list[i + 1] == u[1]) {
					// found an expression:
					list.erase(list.begin() + i + 1);
					list[i] = "#E";
				}
			}
			if (abs_break) break;
		}
		// 3 symbol simplifier:
		abs_break = false;
		if (list.size() > 2) for (int i = 0; i < list.size() - 2; ++i) {
			for (vector<string> u : BINARY_EXPR) {
				if (list.size() <= 2) { abs_break = true; break; }
				if (list[i] == u[0] && list[i + 1] == u[1] && list[i + 2] == u[2]) {
					// found an expression:
					list.erase(list.begin() + i + 2);
					list.erase(list.begin() + i + 1);
					list[i] = "#E";
				}
			}
			if (abs_break) break;
		}

		if (list.size() == 1 && list[0] == "#E") {
			expr = true;
			break;
		}
	}

	return expr;
}
