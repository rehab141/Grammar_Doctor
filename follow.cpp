#include "grammar.h"

void calculateFollow()
{
    if (grammar.empty())
    {
        cout << "\nPlease enter a grammar first.\n";
        return;
    }

    set<char> nonTerminals = getNonTerminals();
    vector< set<char> > follow = getFollowSets();

    cout << "\n---------- FOLLOW Sets ----------\n";

    for (set<char>::iterator nt = nonTerminals.begin(); nt != nonTerminals.end(); ++nt)
    {
        cout << "FOLLOW(" << *nt << ") = { ";

        for (set<char>::iterator it = follow[(int)*nt].begin();
             it != follow[(int)*nt].end(); ++it)
            cout << *it << " ";

        cout << "}\n";
    }
}