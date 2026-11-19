#include "grammar.h"
set<char> firstOfString(string text) {
    set<char> result;
    if (text.empty() || text=="#") { result.insert('#'); return result; }
    bool canEmpty=true;
    for (int i=0; i<(int)text.length(); i++) {
        char c=text[i];
        if (nonTerminals.count(c)==0) {
            result.insert(c); canEmpty=false; break;
        }
        for (set<char>::iterator x=firstSet[c].begin(); x!=firstSet[c].end(); ++x)
            if (*x!='#') result.insert(*x);
        if (firstSet[c].count('#')==0) { canEmpty=false; break; }
    }
    if (canEmpty) result.insert('#');
    return result;
}
void calculateFirst() {
    if (grammar.empty()) { cout << "Please enter a grammar first.\n"; return; }
    firstSet.clear();
    bool changed=true;
    while (changed) {
        changed=false;
        for (map<char, vector<string> >::iterator it=grammar.begin(); it!=grammar.end(); ++it)
            for (int i=0; i<(int)it->second.size(); i++) {
                set<char> temp=firstOfString(it->second[i]);
                for (set<char>::iterator x=temp.begin(); x!=temp.end(); ++x)
                    if (firstSet[it->first].insert(*x).second) changed=true;
            }
    }
    cout << "\n--- FIRST Sets ---\n";
    for (set<char>::iterator n=nonTerminals.begin(); n!=nonTerminals.end(); ++n)
        showSet(*n, firstSet[*n]);
}