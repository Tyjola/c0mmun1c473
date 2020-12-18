#include <iostream>
#include <string>
#include <tuple>

using namespace std;

tuple<int, int> ascii_range() {

    int start_ascii = -1;
    int end_ascii = -1;
    string choice;

    cout << "Default alphabet is ASCII characters beetween 33 and 126." << endl;
    cout << "Do you want to change the alphabet ? [Y/N] : ";
    cin >> choice;
    while (choice != "Y" && choice != "N") {
        cout << "Do you want to change the alphabet ? [Y/N] : ";
        cin >> choice;
    }

    if (choice == "Y") {
        cout << "Help : lowercase alphabet is 97-122 and uppercase alphabet is 65-90." << endl;
        cout << "Please specify the start index in the ASCII table : ";
        cin >> start_ascii;
        while (cin.fail() || start_ascii < 0) {
            cout << "The index must be an integer : ";
            cin.clear();
            cin.ignore(256,'\n');
            cin >> start_ascii;
        }

        cout << "Please specify the end index in the ASCII table : ";
        cin >> end_ascii;
        while (cin.fail() || end_ascii < start_ascii || end_ascii > 126) {
            cout << "The index must be an integer greater than the start index : ";
            cin.clear();
            cin.ignore(256,'\n');
            cin >> end_ascii;
        }
    }
    cout << endl;

    if (start_ascii == -1) { start_ascii = 33; }
    if (end_ascii == -1 ) { end_ascii = 126; }

    return make_tuple(start_ascii, end_ascii);
}