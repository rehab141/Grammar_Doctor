#include "grammar.h"
void generateParsingTable() {
    if (grammar.empty()) { cout << "Please enter a grammar first.\n"; return; }
    calculateFirst();
    calculateFollow();
    map<char, map<char, string> > table;
    bool conflict=false;
    for (map<char, vector<string> >::iterator it=grammar.begin(); it!=grammar.end(); ++it) {
        char left=it->first;
        for (int i=0; i<(int)it->second.size(); i++) {
            string rhs=it->second[i];
            set<char> f=firstOfString(rhs);
            for (set<char>::iterator x=f.begin(); x!=f.end(); ++x) {
                if (*x=='#') continue;
                if (!table[left][*x].empty()) {
                    conflict=true;
                    cout << "Conflict at M[" << left << ", " << *x << "]\n";
                } else table[left][*x]=string(1,left)+"->"+rhs;
            }
            if (f.count('#')) {
                for (set<char>::iterator x=followSet[left].begin(); x!=followSet[left].end(); ++x) {
                    if (!table[left][*x].empty()) {
                        conflict=true;
                        cout << "Conflict at M[" << left << ", " << *x << "]\n";
                    } else table[left][*x]=string(1,left)+"->"+rhs;
                }
            }
        }
    }
    set<char> cols=terminals; cols.insert('$');
    cout << "\n--- LL(1) Parsing Table ---\nNT/T\t";
    for (set<char>::iterator c=cols.begin(); c!=cols.end(); ++c) cout << *c << "\t";
    cout << "\n";
    for (set<char>::iterator r=nonTerminals.begin(); r!=nonTerminals.end(); ++r) {
        cout << *r << "\t";
        for (set<char>::iterator c=cols.begin(); c!=cols.end(); ++c)
            cout << (table[*r][*c].empty() ? "-" : table[*r][*c]) << "\t";
        cout << "\n";
    }
    cout << "\n--- LL(1) Check ---\n";
    if (conflict) cout << "Grammar is NOT LL(1).\nConflict found in parsing table.\n";
    else cout << "Grammar is LL(1).\nNo conflicts found in the parsing table.\n";
}