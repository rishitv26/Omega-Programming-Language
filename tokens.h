#ifndef TOKENS_H
#define TOKENS_H // TODO

struct Identifier { // first define #list, #pointer, #dictionary
	string name; // name of identifier
	TYPE_LATERAL v_type; // its type
	variant<int> value;
};

#endif