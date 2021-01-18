#include <iostream>

#include "caesar.h"

using namespace std;


// Get the offset for the encryption/decryption.
int get_offset(int way) {
    
    int offset;
    if (way == 1) {
    cout << "Please indicate the offset for Caesar's encryption : ";
    }
    else {
        cout << "Please indicate the offset for Caesar's decryption : ";
    }
    cin >> offset;

    while (cin.fail()) {
        cout << "The offset must be an integer : ";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> offset;
    }
    cout << "The offset is : " << offset << endl << endl;
    if (way == 0) { offset = offset * -1; }
    return offset;
    }


// Do the encryption/decryption.
string caesar_encrypt(string content, int offset, int way, int start_ascii, int end_ascii) {   

    int char_val, new_char_val;
    string new_content, new_char;
    for (int i = 0; i < content.length(); i++) {
        char_val = int(content[i]);
        if (char_val != 32) {
            //Iici, on utilise tout simplement le int de décalage pour décalert tout les caractères
            new_char_val = char_val + (offset % (end_ascii - start_ascii));
            
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


// Caesar main function.
string caesar_main(string content, int start_ascii, int end_ascii, int way) {

    int offset;
    offset = get_offset(way);

    string new_content;
    new_content = caesar_encrypt(content, offset, way, start_ascii, end_ascii);

    return new_content;
}

