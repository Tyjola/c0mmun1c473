#include <iostream>

#include "vigenere.h"
#include "key.h"

using namespace std;


// Do the encryption and the decryption.
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


// Vigenere main function.
string vigenere_main(string content, int start_ascii, int end_ascii, int way) {

    string key;
    key = key_main(way, "text");

    string new_content;
    new_content = vigenere_encrypt(content, way, key, start_ascii, end_ascii);

    return new_content;
}