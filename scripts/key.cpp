#include <iostream>
#include <bitset>

#include "streams.h"

using namespace std;


// Get the key for the encryption/decryption from a file or from the console.
string select_key(int way) {

    string content_key;
    string key_way;
    do {
        cout << "Please specify whether you want to add a keyfile (1) or to write the key in the console (0) : ";
        cin >> key_way;
    } while (key_way != "1" && key_way != "0");
    int kw = stoi(key_way);

    if (kw == 1) {
        string keyfile;
        cout << "Please specify the name of the keyfile : ";
        cin >> keyfile;

        content_key = fopen(keyfile);
        if (content_key == "#####error#####") {
            return "#####error#####";
        }
    }
    else {
        if (way == 1) {
        cout << "Please indicate the key for the encryption : ";
        }
        else {
            cout << "Please indicate the key for the decryption : ";
        }
        cin.ignore();
        getline(cin, content_key);
    }
    cout << endl;
    return content_key;
}


// Remove the spaces from the key.
string remove_space(string key) {
    
    string new_key;
    for (int i = 0; i < key.length(); i++){
        if (int(key[i] != 32)) {
            new_key += key[i];
        }
    }
    return new_key;
}
    

// Convert the key in binary format.
string convert_key_binary(string text_key) {

    string binary_text, binary;
    for (int i = 0; i < text_key.length(); i++) {
        binary = bitset<8>(int(text_key[i])).to_string();
        binary_text += binary;
    }
    return binary_text;
}


// Main key function.
string key_main(int way, string output_type) {

    string text_key;
    text_key = select_key(way);
    if (text_key == "#####error#####") {
        return text_key;
    }
    else {
        text_key = remove_space(text_key);

        if (output_type == "binary") {
            string binary_key = convert_key_binary(text_key);
            return binary_key;
        }
        else {
            return text_key;
        }
    }
}