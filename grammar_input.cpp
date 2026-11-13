#include "grammar.h"

void enterGrammar()
{
    int number;
    string production;

    cout << "\nHow many productions do you want to enter? ";
    cin >> number;
    cin.ignore();

    grammar.clear();

    for (int i = 0; i < number; i++)
    {
        cout << "Enter production " << i + 1 << " (example E->E+T|T): ";
        getline(cin, production);
        grammar.push_back(production);
    }

    cout << "\nGrammar saved successfully.\n";
}

void displayGrammar()
{
    if (grammar.empty())
    {
        cout << "\nPlease enter a grammar first.\n";
        return;
    }

    cout << "\n---------- Your Grammar ----------\n";
    for (int i = 0; i < (int)grammar.size(); i++)
    {
        cout << grammar[i] << endl;
    }
}
