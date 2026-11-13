#include "grammar.h"

int main()
{
    int choice;

    do
    {
        cout << "\n====================================\n";
        cout << "           GRAMMAR DOCTOR\n";
        cout << "     Simple Grammar Analysis Tool\n";
        cout << "====================================\n";
        cout << "1. Enter Grammar\n";
        cout << "2. Display Grammar\n";
        cout << "3. Show Grammar Information\n";
        cout << "4. Remove Left Recursion\n";
        cout << "5. Apply Left Factoring\n";
        cout << "6. Calculate FIRST\n";
        cout << "7. Calculate FOLLOW\n";
        cout << "8. Generate LL(1) Parsing Table\n";
        cout << "9. Ambiguous and Unambiguous Examples\n";
        cout << "0. Exit\n";
        cout << "------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                enterGrammar();
                break;
            case 2:
                displayGrammar();
                break;
            case 3:
                showGrammarInfo();
                break;
            case 4:
                removeLeftRecursion();
                break;
            case 5:
                applyLeftFactoring();
                break;
            case 6:
                calculateFirst();
                break;
            case 7:
                calculateFollow();
                break;
            case 8:
                generateParsingTable();
                break;
            case 9:
                showAmbiguityExamples();
                break;
            case 0:
                cout << "\nThank you for using Grammar Doctor!\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}
