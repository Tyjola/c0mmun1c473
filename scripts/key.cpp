#include <iostream>
#include <bitset>
#include <vector>
#include <random>

#include "streams.h"

using namespace std;


// Generate a radom key with a range of characters or an alphabet.
string generate_key(int key_length, int char_key_start, int char_key_end, vector<string> char_key) {

    string key;

    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> distri(char_key_start, char_key_end);

    if (char_key.empty()) {
        for (int i = 0; i < key_length; i++) {
            int index = distri(rng);
            key += char(index);
        }
    }
    else {
        for (int i = 0; i < key_length; i++) {
            key += char_key[distri(rng) % char_key.size()];
        }
    }

    return key;
}


// Get the key for the encryption/decryption from a file or from the console.
string select_key(int way, int key_length, int start_ascii, int end_ascii, vector<string> char_key) {

    string content_key;
    string key_way;
    if (way == 1) {
    do {
        cout << "Please specify whether you want to add a keyfile (0), to write the key in the console (1) or to generate a key (2) : ";
        cin >> key_way;
    } while (key_way != "0" && key_way != "1" && key_way != "2");
    }
    else {
        do {
        cout << "Please specify whether you want to add a keyfile (0) or to write the key in the console (1) : ";
        cin >> key_way;
    } while (key_way != "0" && key_way != "1");
    }

    int kw = stoi(key_way);

    if (kw == 0) {
        string keyfile;
        cout << "Please specify the name of the keyfile : ";
        cin >> keyfile;

        content_key = fopen(keyfile);
        if (content_key == "#####error#####") {
            return "#####error#####";
        }
    }
    else if (kw == 1) {
        if (way == 1) {
        cout << "Please indicate the key for the encryption : ";
        }
        else {
            cout << "Please indicate the key for the decryption : ";
        }
        cin.ignore();
        getline(cin, content_key);
    }
    else if (kw == 2) {
        while (key_length == 0) {
            cout << "Please specify the key's length (must be different from 0) : ";
            cin >> key_length;

            while (cin.fail()) {
                cout << "The length must be an integer : ";
                cin.clear();
                cin.ignore(256,'\n');
                cin >> key_length;
            }
        }
        cout << "Generating the key..." << endl;
        content_key = generate_key(key_length, start_ascii, end_ascii, char_key);
        cout << "The key is : " << content_key << endl;
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
string key_main(int way, string output_type, int key_length, int start_ascii, int end_ascii, vector<string> char_key) {

    string text_key;
    text_key = select_key(way, key_length, start_ascii, end_ascii, char_key);
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