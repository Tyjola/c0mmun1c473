#include <iostream>
#include <fstream>
#include <functional>
#include <string.h>

#include "caesar.h"
#include "vigenere.h"
#include "affine.h"

#include "streams.h"
#include "introduction.h"
#include "flags.h"

using namespace std;

//ceci est un test

int main(int argc, char *argv[]) {   

    introduction();

    if (argc == 1 || argc == 2) {
        help_flag();
        return 0;
    }
    string filename, new_filename, encryption_type;
    for (int i = 1; i < argc; i++) {   
        if (i + 1 != argc) {   
            string arg = argv[i];

            // Displays the help menu.
            if (arg == "-h" || arg == "--help") {
                help_flag();
                return 0;
            }
            // Specifies the name of the file to encrypt.
            if (arg == "-f" || arg == "--filename") {
                filename = argv[i+1];
            }
            // Specifies the name of the file encrypted.
            if (arg == "-o" || arg == "--output") {
                new_filename = argv[i+1];
            }
            // Specifies the encryption type.
            if (arg == "-e" || arg == "--encrypt") {
                encryption_type = argv[i+1];
            }
        }
    }
    int check_flag_error = flags_errors(filename, new_filename, encryption_type);
    if (check_flag_error == 0) {return 0;}

    
    string content;
    content = fopen(filename);
    if (content == "PB") { 
        return 0;
    }
    
    string new_content;
    if (encryption_type == "caesar") {
        new_content = caesar_main(content);
    }
    else if (encryption_type == "vigenere") {
        new_content = vigenere_main(content);
    }
    else if (encryption_type == "affine") {
        new_content = affine_main(content);
    }
    else { 
        cout << "This type of encryption is not recognized : " << encryption_type << endl << endl;
        return 0;
    }

    fcreate(new_filename, new_content);
    cout << "The operation has been performed correctly." << endl << endl;
    return 1;
}

