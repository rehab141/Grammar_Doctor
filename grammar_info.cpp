#include "grammar.h"

void showGrammarInfo()
{
    if (grammar.empty())
    {
        cout << "\nPlease enter a grammar first.\n";
        return;
    }

    set<char> nonTerminals;
    set<char> terminals;
    int productionCount = 0;

    for (int i = 0; i < (int)grammar.size(); i++)
    {
        string line = grammar[i];
        size_t arrow = line.find("->");

        if (arrow == string::npos || arrow == 0)
            continue;

        nonTerminals.insert(line[0]);

        string rightSide = line.substr(arrow + 2);

        for (int j = 0; j < (int)rightSide.length(); j++)
        {
            char symbol = rightSide[j];

            if (symbol == '|')
                productionCount++;
            else if (symbol >= 'A' && symbol <= 'Z')
                nonTerminals.insert(symbol);
            else if (symbol != '#' && symbol != ' ' && symbol != '\'')
                terminals.insert(symbol);
        }

        productionCount++;
    }

    cout << "\n---------- Grammar Information ----------\n";

    cout << "Non-terminals: ";
    for (set<char>::iterator it = nonTerminals.begin(); it != nonTerminals.end(); ++it)
        cout << *it << " ";

    cout << "\nTerminals: ";
    for (set<char>::iterator it = terminals.begin(); it != terminals.end(); ++it)
        cout << *it << " ";

    cout << "\nTotal productions: " << productionCount << endl;
    cout << "\nNote: This project uses single-character grammar symbols.\n";
    cout << "Use # to represent epsilon.\n";
}
