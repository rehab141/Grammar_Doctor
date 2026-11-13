#include "grammar.h"

void showAmbiguityExamples()
{
    cout << "\n---------- Ambiguous Grammar ----------\n";
    cout << "Example:\n";
    cout << "E -> E+E | E*E | id\n";
    cout << "This grammar can produce more than one parse tree for some expressions.\n";
    cout << "For example: id + id * id\n\n";

    cout << "---------- Unambiguous Grammar ----------\n";
    cout << "Example:\n";
    cout << "E -> E+T | T\n";
    cout << "T -> T*F | F\n";
    cout << "F -> id\n";
    cout << "This grammar gives multiplication higher precedence than addition.\n\n";

    cout << "Note: These are teaching examples. The program does not automatically\n";
    cout << "prove whether any arbitrary grammar is ambiguous.\n";
}