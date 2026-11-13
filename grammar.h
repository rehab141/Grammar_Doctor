#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

extern vector<string> grammar;

void enterGrammar();
void displayGrammar();
void showGrammarInfo();

void removeLeftRecursion();
void applyLeftFactoring();

void calculateFirst();
void calculateFollow();
void generateParsingTable();

void showAmbiguityExamples();

set<char> getNonTerminals();
vector< set<char> > getFirstSets();
vector< set<char> > getFollowSets();
set<char> firstOfString(string text, vector< set<char> > firstSets);

#endif
