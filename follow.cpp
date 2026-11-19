#include "grammar.h"
void calculateFollow() {
    if (grammar.empty()) { cout << "Please enter a grammar first.\n"; return; }
    calculateFirst();
    followSet.clear();
    followSet[startSymbol].insert('$');
    bool changed=true;
    while (changed) {
        changed=false;
        for (map<char, vector<string> >::iterator it=grammar.begin(); it!=grammar.end(); ++it) {
            char left=it->first;
            for (int p=0; p<(int)it->second.size(); p++) {
                string rhs=it->second[p];
                for (int i=0; i<(int)rhs.length(); i++) {
                    char current=rhs[i];
                    if (nonTerminals.count(current)==0) continue;
                    string after=rhs.substr(i+1);
                    set<char> temp=firstOfString(after);
                    for (set<char>::iterator x=temp.begin(); x!=temp.end(); ++x)
                        if (*x!='#' && followSet[current].insert(*x).second) changed=true;
                    if (after.empty() || temp.count('#')) {
                        for (set<char>::iterator x=followSet[left].begin(); x!=followSet[left].end(); ++x)
                            if (followSet[current].insert(*x).second) changed=true;
                    }
                }
            }
        }
    }
    cout << "\n--- FOLLOW Sets ---\n";
    for (set<char>::iterator n=nonTerminals.begin(); n!=nonTerminals.end(); ++n)
        showSet(*n, followSet[*n]);
}
