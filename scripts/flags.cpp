#include <iostream>

#include "flags.h"

using namespace std;

int flags_errors(string filename, string encryption_type) {

    if (filename == "") { 
        cout << "Please specify the name of the file to encrypt." << endl << endl;
        return 0;
    }
    else if (encryption_type == "") {
        cout << "Please specify the encryption's type." << endl << endl;
        return 0;
    }
    else {
        return 1;
    }
}

int help_flag() {

    cout << "Commun1c473 is a tool for encrypting and decrypting text contained in a file." << endl;
    cout << "Synopsis : c0mmun1c473 {file to encrypt} {encryption's type} [options]" << endl;
    cout << "The options are : " << endl;
    cout << "- To specify the name of the encrypted file : -o / --output" << endl;
    cout << endl; 
    cout << "Example for Caesar encryption :" << endl;
    cout << "./c0mmun1c473 note.txt caesar -o encrypted_note.txt" << endl;
    cout << "./c0mmun1c473 note_to_encrypt.txt affine --output encrypted_note.txt" << endl;
    cout << endl;
    cout << "The available encryption methods are :" << endl;
    cout << "- Caesar encryption (caesar)" << endl;
    cout << "- Vigenère encryption (vigenere)" << endl;
    cout << "- Affine encryption (affine)" << endl;
    cout << endl;
    return 0;
}