#include "grammar.h"
int main() {
    int choice;
    do {
        cout << "\n========== GRAMMAR DOCTOR ==========\n";
        cout << "1. Enter Grammar\n2. Display Grammar\n3. Calculate FIRST\n4. Calculate FOLLOW\n5. Generate LL(1) Table and Check Grammar\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: enterGrammar(); break;
            case 2: displayGrammar(); break;
            case 3: calculateFirst(); break;
            case 4: calculateFollow(); break;
            case 5: generateParsingTable(); break;
            case 0: cout << "Program ended. Thank you!\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
    return 0;
}