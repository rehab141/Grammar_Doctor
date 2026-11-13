#include "grammar.h"

void calculateFirst()
{
    if (grammar.empty())
    {
        cout << "\nPlease enter a grammar first.\n";
        return;
    }

    set<char> nonTerminals = getNonTerminals();
    vector< set<char> > first = getFirstSets();

    cout << "\n---------- FIRST Sets ----------\n";

    for (set<char>::iterator nt = nonTerminals.begin(); nt != nonTerminals.end(); ++nt)
    {
        cout << "FIRST(" << *nt << ") = { ";

        for (set<char>::iterator it = first[(int)*nt].begin();
             it != first[(int)*nt].end(); ++it)
            cout << *it << " ";

        cout << "}\n";
    }
}