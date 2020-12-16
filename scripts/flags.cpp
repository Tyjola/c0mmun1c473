#include <iostream>

#include "flags.h"

using namespace std;

int flags_errors(string filename, string new_filename, string encryption_type) {

    if (filename == "") { 
        cout << "Please specify the name of the file to encrypt." << endl;
        cout << "Use the flag : -f / --filename" << endl << endl;
        return 0;
    }
    if (new_filename == "") {
        cout << "Please specify the name of the encrypted file." << endl;
        cout << "Use the flag : -o / --output" << endl << endl;
        return 0;
    }
    if (encryption_type == "") {
        cout << "Please specify the encryption's type." << endl;
        cout << "Use the flag : -e / --encrypt" << endl << endl;
        return 0;
    }
    else {
        return 1;
    }
}

int help_flag() {

    cout << "Commun1c473 is a tool for encrypting text contained in a file." << endl;
    cout << "The flags are : " << endl;
    cout << "- To specify the file to encrypt : -f / --filename" << endl;
    cout << "- To specify the name of the encrypted file : -o / --output" << endl;
    cout << "- To specify the encryption's type : -e / --encrypt" << endl;
    cout << endl; 
    cout << "Example for Caesar encryption :" << endl;
    cout << "./c0mmun1c473 -f note.txt -o encrypted_note.txt -e caesar";
    cout << "./c0mmun1c473 --filename note.txt --output encrypted_note.txt --encrypt caesar" << endl;
    cout << endl;
    cout << "The available encryption methods are :" << endl;
    cout << "- Caesar encryption" << endl;
    cout << "- Vigenère encryption" << endl;
    cout << endl;
    return 0;
}