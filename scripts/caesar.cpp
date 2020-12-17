#include <iostream>

#include "caesar.h"

using namespace std;


int get_way_caesar() {
    string way;
    do {
        cout << "Please specify if it is an encryption (1) or a decryption (0) : ";
        cin >> way;
        cout << endl;
    } while (way != "1" && way != "0");

    return stoi(way);
}


int get_offset(int way) {
    
    int offset;
    if (way == 1) {
    cout << "Please indicate the offset for Caesar's encryption : ";
    }
    else {
        cout << "Please indicate the offset for Caesar's decryption : ";
    }
    cin >> offset;

    while(cin.fail()) {
        cout << "The offset must be an integer : ";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> offset;
    }
    cout << endl << "The offset is : " << offset << endl << endl;
    if (way == 0) { offset = offset * -1; }
    return offset;
    }


string caesar_encrypt(string content, int offset, int way) {   

    int beggin_ascii = 33;
    int end_ascii = 126;

    int char_val, new_char_val;
    string new_content, new_char;
    for (int i = 0; i < content.length(); i++) {
        char_val = int(content[i]);
        if (char_val != 32) {
            new_char_val = char_val + (offset % (end_ascii - beggin_ascii));
            
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



string caesar_main(string content) {
    
    int way;
    way = get_way_caesar();

    int offset;
    offset = get_offset(way);

    string new_content;
    new_content = caesar_encrypt(content, offset, way);

    return new_content;
}

