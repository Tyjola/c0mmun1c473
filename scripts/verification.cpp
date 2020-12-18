#include <iostream>

using namespace std;

int main() {

    int start_ascii, end_ascii;

    cout << "Please specify the range of the ASCII characters used in the text (default will be 33-126)." << endl;
    cout << "Help : lowercase alphabet is 97-122 and uppercase alphabet is 65-90" << endl;

    cout << "Please specify the start index : ";
    cin >> start_ascii;
    while (cin.fail()) {
        cout << "The index must be an integer : ";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> start_ascii;
    }

    cout << "Please specify the end index : ";
    cin >> end_ascii;
    while (cin.fail() or end_ascii < start_ascii) {
        cout << "The index must be an integer greater than the start index : ";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> end_ascii;
    }

}