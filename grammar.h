#ifndef GRAMMAR_H
#define GRAMMAR_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;
extern map<char, vector<string> > grammar;
extern set<char> nonTerminals, terminals;
extern char startSymbol;
extern map<char, set<char> > firstSet, followSet;
void enterGrammar();
void displayGrammar();
void findTerminals();
void calculateFirst();
void calculateFollow();
set<char> firstOfString(string text);
void generateParsingTable();
void showSet(char symbol, set<char> values);
#endif