#include <iostream>
#include <tuple>

#include "affine.h"

using namespace std;


tuple<int, int> get_coefficients_affine() {
    int a,b;
    cout << "The encryption key must be of type (a,b) (a and b integers)." << endl;

    cout << "Please specify the value of a : ";
    cin >> a;
    cout << "Please specify the value of b : ";
    cin >> b;

    cout << "Your key is : (" << a <<"," << b <<")" << endl << endl;
    return make_tuple(a, b);
}


string affine_encrypt(string content, int a, int b, int start_ascii, int end_ascii) {

    int char_val, new_char_val, offset;
    string new_content, new_char;
    for (int i = 0; i < content.length(); i++) {
        char_val = int(content[i]);

        if (char_val != 32) {
            new_char_val = (((a * (char_val - start_ascii)) + b ) % ((end_ascii - start_ascii) + 1)) + start_ascii;
            new_char = char(new_char_val);
        }
        else {
            new_char = " ";
        }
        new_content += new_char;
    }
    return new_content;
}


string affine_decrypt(string content, int a, int b, int start_ascii, int end_ascii) {

    int diff_ascii = (end_ascii - start_ascii) + 1;

    int a_inverse;
    int k;
    for (int i = 0; i < diff_ascii; i++) {
        k = (a * i) % diff_ascii;
        if (k == 1) {
            a_inverse = i;
        }
    }

    string new_content;
    int char_val;
    for (int i = 0; i < content.length(); i++) {
        char_val = int(content[i]);
        if(char_val != 32) {
            new_content = new_content + char(((a_inverse * ((diff_ascii + char_val - start_ascii - b)) % diff_ascii)) + start_ascii);
        }
        else {
            new_content += " ";
        }     
    }
    return new_content;
}


string affine_main(string content, int start_ascii, int end_ascii, int way) {

    int a,b;
    tie(a, b) = get_coefficients_affine();

    string new_content;
    if (way == 1) {
        new_content = affine_encrypt(content, a, b, start_ascii, end_ascii);
    }
    else {
        new_content = affine_decrypt(content, a, b, start_ascii, end_ascii);
    }
    return new_content;
}