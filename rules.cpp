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
	// 2 symbol simplfier:
	string current = "";
	for (int i = 0; i < list.size() - 1; ++i) {
		for (vector<string> u : UNARY_EXPR) {
			if (list[i] == u[0] && list[i + 1] == u[1]) {
				// found an expression:
				
			}
		}
	}
	// now its composed of #I's & #L's


	return expr;
}
