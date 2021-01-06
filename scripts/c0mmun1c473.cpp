#include <iostream>
#include <fstream>
#include <functional>
#include <string.h>

#include "caesar.h"
#include "vigenere.h"
#include "affine.h"
#include "DES.h"

#include "streams.h"
#include "introduction.h"
#include "flags.h"
#include "verification.h"

using namespace std;

int main(int argc, char *argv[]) {   

    // Display the introduction.
    introduction();

    // Check for the arguments.
    if (argc == 1) {
        help_flag();
        return 0;
    }
    string filename, new_filename, encryption_type;
    for (int i = 1; i < argc; i++) {  
        string arg = argv[i]; 
        // Display the help menu.
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
    // If the filename of the encryption's type is missing, the program ends.
    int check_flag_error = flags_errors(new_filename, encryption_type);
    if (check_flag_error == 0) {return 0;}

    
    // Open the file to encrypt to get the content.
    string content;
    content = fopen(filename);
    if (content == "#####error#####") { 
        return 0;
    }


    // Check if the content contains characters of the extended ascii table.
    int content_allowed;
    content_allowed = check_content(content);
    if (content_allowed == 0) {
        return 0;
    }


    // Ask if the operation is an encryption or a decryption.
    string way_str;
    do {
        cout << "Please specify if it is an encryption (1) or a decryption (0) : ";
        cin >> way_str;
        cout << endl;
    } while (way_str != "1" && way_str != "0");
    int way = stoi(way_str);


    // Change the alphabet if needed.
    int start_ascii, end_ascii;
    tie(start_ascii, end_ascii) = ascii_range();


    // Select the right encryption's type.
    string new_content;
    if (encryption_type == "caesar") {
        new_content = caesar_main(content, start_ascii, end_ascii, way);
    }
    else if (encryption_type == "vigenere") {
        new_content = vigenere_main(content, start_ascii, end_ascii, way);
    }
    else if (encryption_type == "affine") {
        new_content = affine_main(content, start_ascii, end_ascii, way);
    }
    else if (encryption_type == "DES") {
        new_content = DES_main(content, way);
    }
    else { 
        cout << "This type of encryption is not recognized : " << encryption_type << endl << endl;
        return 0;
    }


    // Check if the new file has been correctly created.
    int success = fcreate(new_filename, new_content);

    // Display whether the operation worked or not.
    if (success = 1) {
        if (way == 1) {
            cout << "The encryption has been performed correctly." << endl << endl;
        }
        else {
            cout << "The decryption has been performed correctly." << endl << endl;
        }
    }
    else {
        if (way == 1) {
            cout << "The encryption did not go well." << endl << endl;
        }
        else {
            cout << "The decryption did not go well." << endl << endl;
        }
    }
    return 1;
}

