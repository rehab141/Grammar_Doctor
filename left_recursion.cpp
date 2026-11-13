#include "grammar.h"

void removeLeftRecursion()
{
    if (grammar.empty())
    {
        cout << "\nPlease enter a grammar first.\n";
        return;
    }

    vector<string> newGrammar;
    bool found = false;

    for (int i = 0; i < (int)grammar.size(); i++)
    {
        string line = grammar[i];
        size_t arrow = line.find("->");

        if (arrow == string::npos || arrow == 0)
        {
            newGrammar.push_back(line);
            continue;
        }

        char A = line[0];
        string rightSide = line.substr(arrow + 2);

        vector<string> alternatives;
        string part = "";

        for (int j = 0; j <= (int)rightSide.length(); j++)
        {
            if (j == (int)rightSide.length() || rightSide[j] == '|')
            {
                alternatives.push_back(part);
                part = "";
            }
            else
                part += rightSide[j];
        }

        vector<string> alpha;
        vector<string> beta;

        for (int j = 0; j < (int)alternatives.size(); j++)
        {
            if (alternatives[j].length() > 0 && alternatives[j][0] == A)
                alpha.push_back(alternatives[j].substr(1));
            else
                beta.push_back(alternatives[j]);
        }

        if (alpha.empty())
        {
            newGrammar.push_back(line);
            continue;
        }

        if (beta.empty())
        {
            cout << "\nCannot remove left recursion from " << A
                 << " because it has no non-recursive alternative.\n";
            newGrammar.push_back(line);
            continue;
        }

        char newSymbol = 'Z';
        while (newSymbol >= 'A' && newSymbol <= 'Z')
        {
            bool used = false;

            for (int k = 0; k < (int)grammar.size(); k++)
            {
                if (grammar[k].length() > 0 && grammar[k][0] == newSymbol)
                    used = true;
            }

            for (int k = 0; k < (int)newGrammar.size(); k++)
            {
                if (newGrammar[k].length() > 0 && newGrammar[k][0] == newSymbol)
                    used = true;
            }

            if (!used && newSymbol != A)
                break;

            newSymbol--;
        }

        if (newSymbol < 'A')
        {
            cout << "\nNo free capital letter is available for a new non-terminal.\n";
            newGrammar.push_back(line);
            continue;
        }

        string firstLine = "";
        for (int j = 0; j < (int)beta.size(); j++)
        {
            if (j > 0) firstLine += "|";
            firstLine += beta[j] + newSymbol;
        }

        string secondLine = "";
        for (int j = 0; j < (int)alpha.size(); j++)
        {
            if (j > 0) secondLine += "|";
            secondLine += alpha[j] + newSymbol;
        }
        secondLine += "|#";

        newGrammar.push_back(string(1, A) + "->" + firstLine);
        newGrammar.push_back(string(1, newSymbol) + "->" + secondLine);
        found = true;
    }

    grammar = newGrammar;

    cout << "\n---------- Left Recursion Result ----------\n";
    if (!found)
        cout << "No direct left recursion was found.\n";

    for (int i = 0; i < (int)grammar.size(); i++)
        cout << grammar[i] << endl;

    cout << "\nNote: This module handles direct left recursion.\n";
}
