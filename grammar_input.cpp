#include "grammar.h"
map<char, vector<string> > grammar;
set<char> nonTerminals, terminals;
char startSymbol = 0;
map<char, set<char> > firstSet, followSet;

void enterGrammar() {
    grammar.clear(); nonTerminals.clear(); terminals.clear(); startSymbol = 0;
    firstSet.clear(); followSet.clear();
    int n;
    cout << "Enter number of productions: ";
    cin >> n; cin.ignore();
    for (int i=0; i<n; i++) {
        string line;
        cout << "Enter production " << i+1 << " (example E->TA|#): ";
        getline(cin, line);
        if (line.length()<4 || line.substr(1,2)!="->") {
            cout << "Invalid format. Use A->... format.\n";
            i--; continue;
        }
        char left=line[0];
        if (i == 0) startSymbol = left;
        nonTerminals.insert(left);
        string rhs=line.substr(3), part="";
        for (int j=0; j<(int)rhs.length(); j++) {
            if (rhs[j]=='|') { grammar[left].push_back(part); part=""; }
            else part+=rhs[j];
        }
        grammar[left].push_back(part);
    }
    findTerminals();
    cout << "Grammar entered successfully!\n";
}
void displayGrammar() {
    if (grammar.empty()) { cout << "Please enter a grammar first.\n"; return; }
    cout << "\n--- Your Grammar ---\n";
    for (map<char, vector<string> >::iterator it=grammar.begin(); it!=grammar.end(); ++it) {
        cout << it->first << " -> ";
        for (int i=0; i<(int)it->second.size(); i++) {
            cout << it->second[i];
            if (i != (int)it->second.size()-1) cout << " | ";
        }
        cout << endl;
    }
}
void findTerminals() {
    terminals.clear();
    for (map<char, vector<string> >::iterator it=grammar.begin(); it!=grammar.end(); ++it)
        for (int i=0; i<(int)it->second.size(); i++)
            for (int j=0; j<(int)it->second[i].length(); j++) {
                char c=it->second[i][j];
                if (c!='#' && nonTerminals.count(c)==0) terminals.insert(c);
            }
}