#include "grammar.h"

void generateParsingTable()
{
    if (grammar.empty())
    {
        cout << "\nPlease enter a grammar first.\n";
        return;
    }

    set<char> nonTerminals = getNonTerminals();
    vector< set<char> > first = getFirstSets();
    vector< set<char> > follow = getFollowSets();

    vector<char> terminals;
    for (int i = 0; i < (int)grammar.size(); i++)
    {
        string line = grammar[i];
        size_t arrow = line.find("->");
        if (arrow == string::npos) continue;

        string right = line.substr(arrow + 2);

        for (int j = 0; j < (int)right.length(); j++)
        {
            char symbol = right[j];

            if (symbol != '|' && symbol != '#' &&
                nonTerminals.count(symbol) == 0 &&
                find(terminals.begin(), terminals.end(), symbol) == terminals.end())
            {
                terminals.push_back(symbol);
            }
        }
    }

    if (find(terminals.begin(), terminals.end(), '$') == terminals.end())
        terminals.push_back('$');

    string table[256][256];
    bool conflict = false;

    for (int i = 0; i < (int)grammar.size(); i++)
    {
        string line = grammar[i];
        size_t arrow = line.find("->");
        if (arrow == string::npos || arrow == 0) continue;

        char left = line[0];
        string right = line.substr(arrow + 2);
        string alternative = "";

        for (int j = 0; j <= (int)right.length(); j++)
        {
            if (j == (int)right.length() || right[j] == '|')
            {
                set<char> currentFirst = firstOfString(alternative, first);

                for (set<char>::iterator it = currentFirst.begin();
                     it != currentFirst.end(); ++it)
                {
                    if (*it != '#')
                    {
                        if (table[(int)left][(int)*it] != "")
                            conflict = true;

                        table[(int)left][(int)*it] = string(1, left) + "->" + alternative;
                    }
                }

                if (currentFirst.count('#') > 0)
                {
                    for (set<char>::iterator it = follow[(int)left].begin();
                         it != follow[(int)left].end(); ++it)
                    {
                        if (table[(int)left][(int)*it] != "")
                            conflict = true;

                        table[(int)left][(int)*it] = string(1, left) + "->" + alternative;
                    }
                }

                alternative = "";
            }
            else
                alternative += right[j];
        }
    }

    cout << "\n---------- LL(1) Parsing Table ----------\n";
    cout << "NT/T\t";

    for (int i = 0; i < (int)terminals.size(); i++)
        cout << terminals[i] << "\t";

    cout << endl;

    for (set<char>::iterator nt = nonTerminals.begin(); nt != nonTerminals.end(); ++nt)
    {
        cout << *nt << "\t";

        for (int i = 0; i < (int)terminals.size(); i++)
        {
            string cell = table[(int)*nt][(int)terminals[i]];

            if (cell == "")
                cout << "-\t";
            else
                cout << cell << "\t";
        }

        cout << endl;
    }

    cout << "\nFinal Result: ";

    if (conflict)
        cout << "Grammar is NOT LL(1) because a table conflict exists.\n";
    else
        cout << "No table conflict found. Grammar is LL(1) for this simple input.\n";
}