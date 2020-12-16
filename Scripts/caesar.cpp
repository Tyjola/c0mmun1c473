#include <iostream>

#include "caesar.h"

using namespace std;



int get_offset() {
    
    int offset;
    cout << "Please indicate the offset for Caesar's encryption : ";
    cin >> offset;
    return offset;
    }


string caesar_encrypt(string content, int offset) {   

    int beggin_ascii = 32;
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
    
    int offset;
    string new_content;

    offset = get_offset();
    new_content = caesar_encrypt(content, offset);

    return new_content;
}

