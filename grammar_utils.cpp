#include "grammar.h"
void showSet(char symbol, set<char> values) {
    cout << symbol << " = { ";
    for (set<char>::iterator it=values.begin(); it!=values.end(); ++it) {
        cout << *it;
        set<char>::iterator nextIt=it; ++nextIt;
        if (nextIt!=values.end()) cout << ", ";
    }
    cout << " }\n";
}