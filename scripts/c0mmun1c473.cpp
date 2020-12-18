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
#include "verification.h"

using namespace std;

int main(int argc, char *argv[]) {   

    introduction();

    int start_ascii, end_ascii;
    tie(start_ascii, end_ascii) = ascii_range();

    if (argc == 1) {
        help_flag();
        return 0;
    }
    string filename, new_filename, encryption_type;
    for (int i = 1; i < argc; i++) {  
        string arg = argv[i]; 
        // Displays the help menu.
        if (arg == "-h" || arg == "--help") {
            help_flag();
            return 0;
        }

        if (i == 1 or i == 2) {   
            // Specifies the name of the file to encrypt.
            if (i == 1) {
                filename = argv[i];
            }
            // Specifies the encryption type.
            else if (i == 2) {
                encryption_type = argv[i];
            }
        }

        if (i > 2) {
            // Specifies the name of the file encrypted.
            if (arg == "-o" || arg == "--output") {
                new_filename = argv[i+1];
            }
        }
    }

    if (new_filename == "") {
        new_filename = "encrypted_"+filename;
    }

    int check_flag_error = flags_errors(new_filename, encryption_type);
    if (check_flag_error == 0) {return 0;}

    
    string content;
    content = fopen(filename);
    if (content == "PB") { 
        return 0;
    }
    
    string new_content;
    if (encryption_type == "caesar") {
        new_content = caesar_main(content, start_ascii, end_ascii);
    }
    else if (encryption_type == "vigenere") {
        new_content = vigenere_main(content, start_ascii, end_ascii);
    }
    else if (encryption_type == "affine") {
        new_content = affine_main(content, start_ascii, end_ascii);
    }
    else { 
        cout << "This type of encryption is not recognized : " << encryption_type << endl << endl;
        return 0;
    }

    fcreate(new_filename, new_content);
    cout << "The operation has been performed correctly." << endl << endl;
    return 1;
}

