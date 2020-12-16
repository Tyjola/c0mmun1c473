#include <iostream>
// #include <string>

#include "vigenere.h"

using namespace std;


int get_way() {
    string way;
    do {
        cout << "Please specify if it is an encryption (1) or a decryption (0) : ";
        cin >> way;
        cout << endl;
    } while (way != "1" && way != "0");

    return stoi(way);
}


string get_key(int way) {
    string key;
    if (way == 1) {
        cout << "Please indicate the key for the Vigenere encryption : ";
    }
    else {
        cout << "Please indicate the key for the Vigenere decryption : ";
    }
    cin >> key;
    cout << endl;
    if (way == 1) {
        cout << "Encryption of the file with the key : " << key << endl;
    }
    else {
        cout << "Decryption of the file with the key : " << key << endl;
    }
    cout << endl;
    return key;
}


string vigenere_encrypt(string content, int way, string key) {

    int beggin_ascii = 33;
    int end_ascii = 126;

    int key_length = key.length();
    
    int char_val, new_char_val, offset;
    string new_content, new_char;
    for (int i = 0; i < content.length(); i++) {
        char_val = int(content[i]);

        if (char_val != 32) {
            offset = int(key[i % key_length]) - beggin_ascii;
            if (way == 0) { offset = offset * -1; }
            new_char_val = char_val + offset;

            if (new_char_val > end_ascii) {
                new_char_val = (new_char_val % end_ascii) + beggin_ascii;
            }
            if (new_char_val < beggin_ascii) {
                new_char_val = end_ascii - (beggin_ascii - new_char_val);
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


string vigenere_main(string content) {

    int way;
    string key;
    string new_content;

    way = get_way();
    key = get_key(way);
    new_content = vigenere_encrypt(content, way, key);

    return new_content;
}