#include "grammar.h"

void applyLeftFactoring()
{
    if (grammar.empty())
    {
        cout << "\nPlease enter a grammar first.\n";
        return;
    }

    vector<string> newGrammar;
    bool changed = false;

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

        bool factored = false;

        for (int a = 0; a < (int)alternatives.size() && !factored; a++)
        {
            for (int b = a + 1; b < (int)alternatives.size() && !factored; b++)
            {
                int length = 0;

                while (length < (int)alternatives[a].length() &&
                       length < (int)alternatives[b].length() &&
                       alternatives[a][length] == alternatives[b][length])
                {
                    length++;
                }

                if (length > 0)
                {
                    string prefix = alternatives[a].substr(0, length);
                    string restA = alternatives[a].substr(length);
                    string restB = alternatives[b].substr(length);

                    char newSymbol = 'Z';
                    while (newSymbol >= 'A' && newSymbol <= 'Z')
                    {
                        bool used = false;
                        for (int k = 0; k < (int)grammar.size(); k++)
                            if (grammar[k].length() > 0 && grammar[k][0] == newSymbol)
                                used = true;

                        for (int k = 0; k < (int)newGrammar.size(); k++)
                            if (newGrammar[k].length() > 0 && newGrammar[k][0] == newSymbol)
                                used = true;

                        if (!used && newSymbol != A)
                            break;
                        newSymbol--;
                    }

                    if (newSymbol < 'A')
                        continue;

                    string mainRight = "";
                    for (int k = 0; k < (int)alternatives.size(); k++)
                    {
                        if (k == a || k == b)
                            continue;
                        if (mainRight != "") mainRight += "|";
                        mainRight += alternatives[k];
                    }

                    if (mainRight != "") mainRight += "|";
                    mainRight += prefix;
                    mainRight += newSymbol;

                    string extraRight = restA;
                    if (extraRight == "") extraRight = "#";
                    extraRight += "|";
                    if (restB == "") restB = "#";
                    extraRight += restB;

                    newGrammar.push_back(string(1, A) + "->" + mainRight);
                    newGrammar.push_back(string(1, newSymbol) + "->" + extraRight);

                    factored = true;
                    changed = true;
                }
            }
        }

        if (!factored)
            newGrammar.push_back(line);
    }

    grammar = newGrammar;

    cout << "\n---------- Left Factoring Result ----------\n";
    if (!changed)
        cout << "No common prefix was found.\n";

    for (int i = 0; i < (int)grammar.size(); i++)
        cout << grammar[i] << endl;

    cout << "\nNote: This module removes one common prefix at a time.\n";
}