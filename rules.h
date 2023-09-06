#ifndef RULES_H
#define RULES_H

#define MAX_SHARED_NODES 100

// defines what defines the fundamental rules
class RuleBody {
private:
	string title;
	RuleBody* next[MAX_SHARED_NODES];
public:
	RuleBody(string t, RuleBody *ptr1 = nullptr, RuleBody* ptr2 = nullptr) :title(t) {
		next[0] = ptr1;
		next[1] = ptr2;
	};

	RuleBody& get_next(int index = 0);
	void set_index(RuleBody* val, int index = 0);
};

map<string, vector<RuleBody*>> Rules;
void initRules();
void endRules();

#endif
