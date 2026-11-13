#include "grammar.h"

set<char> getNonTerminals()
{
    set<char> nonTerminals;

    for (int i = 0; i < (int)grammar.size(); i++)
    {
        size_t arrow = grammar[i].find("->");
        if (arrow != string::npos && arrow > 0)
            nonTerminals.insert(grammar[i][0]);
    }

    return nonTerminals;
}

set<char> firstOfString(string text, vector< set<char> > firstSets)
{
    set<char> result;
    set<char> nonTerminals = getNonTerminals();

    if (text == "#" || text == "")
    {
        result.insert('#');
        return result;
    }

    bool allCanBeEmpty = true;

    for (int i = 0; i < (int)text.length(); i++)
    {
        char symbol = text[i];

        if (symbol == ' ')
            continue;

        if (symbol == '#')
        {
            result.insert('#');
            break;
        }

        if (nonTerminals.count(symbol) == 0)
        {
            result.insert(symbol);
            allCanBeEmpty = false;
            break;
        }

        for (set<char>::iterator it = firstSets[(int)symbol].begin();
             it != firstSets[(int)symbol].end(); ++it)
        {
            if (*it != '#')
                result.insert(*it);
        }

        if (firstSets[(int)symbol].count('#') == 0)
        {
            allCanBeEmpty = false;
            break;
        }
    }

    if (allCanBeEmpty)
        result.insert('#');

    return result;
}

vector< set<char> > getFirstSets()
{
    vector< set<char> > first(256);
    set<char> nonTerminals = getNonTerminals();

    bool changed = true;

    while (changed)
    {
        changed = false;

        for (int i = 0; i < (int)grammar.size(); i++)
        {
            string line = grammar[i];
            size_t arrow = line.find("->");
            if (arrow == string::npos || arrow == 0)
                continue;

            char left = line[0];
            string right = line.substr(arrow + 2);
            string alternative = "";

            for (int j = 0; j <= (int)right.length(); j++)
            {
                if (j == (int)right.length() || right[j] == '|')
                {
                    set<char> current = firstOfString(alternative, first);

                    for (set<char>::iterator it = current.begin(); it != current.end(); ++it)
                    {
                        if (first[(int)left].insert(*it).second)
                            changed = true;
                    }

                    alternative = "";
                }
                else
                    alternative += right[j];
            }
        }
    }

    return first;
}

vector< set<char> > getFollowSets()
{
    vector< set<char> > first = getFirstSets();
    vector< set<char> > follow(256);
    set<char> nonTerminals = getNonTerminals();

    if (grammar.size() > 0 && grammar[0].length() > 0)
        follow[(int)grammar[0][0]].insert('$');

    bool changed = true;

    while (changed)
    {
        changed = false;

        for (int i = 0; i < (int)grammar.size(); i++)
        {
            string line = grammar[i];
            size_t arrow = line.find("->");
            if (arrow == string::npos || arrow == 0)
                continue;

            char left = line[0];
            string right = line.substr(arrow + 2);
            string alternative = "";

            for (int j = 0; j <= (int)right.length(); j++)
            {
                if (j == (int)right.length() || right[j] == '|')
                {
                    for (int k = 0; k < (int)alternative.length(); k++)
                    {
                        char symbol = alternative[k];

                        if (nonTerminals.count(symbol) > 0)
                        {
                            string remaining = alternative.substr(k + 1);
                            set<char> nextFirst = firstOfString(remaining, first);

                            for (set<char>::iterator it = nextFirst.begin();
                                 it != nextFirst.end(); ++it)
                            {
                                if (*it != '#' && follow[(int)symbol].insert(*it).second)
                                    changed = true;
                            }

                            if (remaining == "" || nextFirst.count('#') > 0)
                            {
                                for (set<char>::iterator it = follow[(int)left].begin();
                                     it != follow[(int)left].end(); ++it)
                                {
                                    if (follow[(int)symbol].insert(*it).second)
                                        changed = true;
                                }
                            }
                        }
                    }

                    alternative = "";
                }
                else
                    alternative += right[j];
            }
        }
    }

    return follow;
}