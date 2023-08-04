#include "common.h"

vector<string> split_by(string str, char by)
{
    vector<string> out;
    out.push_back(""); // initial item

    for (char i : str) {
        if (i == by) out.push_back("");
        else out.back() += i;
    }

    return out;
}

static int find(string str, char c)
{
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == c) return i;
    }
    return -1;
}

string vect_to_str(vector<string> vect, char c) {
    string out;

    for (const string& i : vect) {
        out += i + c;
    }

    return out;
}

static void replace_substring(vector<string>* lines, string substring, string desired) {
    for (int i = 0; i < lines->size(); ++i) {
        // for each line:
        vector<string> l = *lines;
        for (int k = 0; k < l[i].size(); ++k) {
            if (k + substring.size() > l[i].size()) break; // or else this will generate an error:
            // read string from k, k + substring.size()
            string str = "";
            for (int j = k; j <= k + substring.size(); ++j) {
                str += l[i][j];
            }
            if (str == substring) {
                // found substring starting at k, now to replace it all with desired.
                for (int p = 0; p < substring.size(); ++p) {
                    if (p < desired.size()) {
                        // replace character with own:
                        l[i][k+p] = desired[p];
                    }
                    else {
                        l[i].erase(l[i].begin() + k + p);
                    }
                }
            }
        }
    }
}

bool LEXER_SIMPLIFIED(vector<string> *lines)
{
	for (const string& i : *lines) {
        if (find(i, ';') >= 0) return false;
        else if ( // register special line-to-line conditions here.
            i == "" ||
            i == " " ||
            i == "\t"
            ) return false;
	}

    return true;
}

void LEXER_SIMPLIFY(vector<string>* lines, int* counter)
{
    string l = (*lines)[*counter]; // string we care about (starts as first one)

    if (l[0] == ' ' || l[0] == '\t') {
        (*lines)[*counter].erase((*lines)[*counter].begin() + 0);
        return void(); // check this line again sometime.
    }
    // update l:
    l = (*lines)[*counter];

    if (find(l, ';') >= 0) { // if there is a comment:
        int comment_location = find(l, ';');
        (*lines)[*counter].erase(comment_location); // erase comment from that point
    }
    // update l:
    l = (*lines)[*counter];

    if (l == "" || l == "\t" || l == " ") // if it is a whitespace:
    {
        lines->erase((*lines).begin() + *counter);
    }
    else { // if current line is simplified, go to the next one.
        *counter += 1;
    }
    
}

void LEXER_FIND_CONSTANTS(vector<int>* indexs, vector<string>* lines, struct Symbols *sym)
{
    for (int i = 0; i < lines->size(); ++i) {
        string word = "";
        for (const char c : (*lines)[i]) {
            word += c;
            if (word == sym->CONSTANT) {
                // yay found constant line, slap this in indexs.
                indexs->push_back(i);
            }
            else if (word.size() == sym->CONSTANT.size()) break; // no point of checking farther
        }
    }
}

void LEXER_REMOVE_LINES(vector<int>* indexs, vector<string>* lines)
{
    for (int i : *indexs) {
        lines->erase(lines->begin() + i);
        for (int j = 0; j < indexs->size(); ++j) {
            if ((*indexs)[j] > i) { --(*indexs)[j]; }
        }
    }
}

void LEXER_FILL_CONST_TABLE(vector<int>* indexs, vector<string>* lines, map <string, string> *constants)
{
    for (int i : *indexs) {
        vector<string> l = split_by((*lines)[i]);
        (*constants)[l[1]] = l[2]; // if this goes wrong, imply constant was not defined correctly.
    }
}

void LEXER_REPLACE_CONSTANTS(map<string, string>* constants, vector<string>* lines)
{
    for (int i = 0; i < lines->size(); ++i) {
        for (const auto& constant : *constants) {
            while ((*lines)[i].find(constant.first) != 18446744073709551615) { // while its present
                // replace_substring(lines, constant.first, constant.second);
                if (constant.first.size() >= constant.second.size())
                    (*lines)[i].replace((*lines)[i].find(constant.first), constant.first.size(), constant.second);
                string code = vect_to_str(*lines, '\n');
                cout << code << endl;
            }
        }
    }
}
