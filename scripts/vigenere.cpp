#include <iostream>

#include "vigenere.h"

using namespace std;


string get_key_vigenere(int way) {
    string key;
    if (way == 1) {
        cout << "Please indicate the key for the Vigenere encryption : ";
    }
    else {
        cout << "Please indicate the key for the Vigenere decryption : ";
    }
    cin.ignore();
    getline(cin, key);
    if (way == 1) {
        cout << "Encryption of the file with the key : " << key << endl;
    }
    else {
        cout << "Decryption of the file with the key : " << key << endl;
    }
    cout << endl;
    return key;
}


string vigenere_encrypt(string content, int way, string key, int start_ascii, int end_ascii) {

    int key_length = key.length();
    
    int char_val, new_char_val, offset;
    string new_content, new_char;
    for (int i = 0; i < content.length(); i++) {
        char_val = int(content[i]);

        if (char_val != 32) {
            offset = int(key[i % key_length]) - start_ascii;
            if (way == 0) { offset = offset * -1; }
            new_char_val = char_val + offset;

            if (new_char_val > end_ascii) {
                new_char_val = (new_char_val % end_ascii) + start_ascii;
            }
            if (new_char_val < start_ascii) {
                new_char_val = end_ascii - (start_ascii - new_char_val);
            }
            new_char = char(new_char_val);
        }
        else {
            new_char = " ";
        }
        new_content += new_char;
    }
    return new_content;
}


string vigenere_main(string content, int start_ascii, int end_ascii, int way) {

    string key;
    key = get_key_vigenere(way);

    string new_content;
    new_content = vigenere_encrypt(content, way, key, start_ascii, end_ascii);

    return new_content;
}