#include <iostream>
#include <tuple>

#include "affine.h"

using namespace std;


int beggin_ascii = 33;
int end_ascii = 126;


tuple<int, int> get_coefficients_affine() {
    int a,b;
    cout << "The encryption key must be of type (a,b) (a and b integers)." << endl << endl;

    cout << "Please specify the value of a : ";
    cin >> a;
    cout << "Please specify the value of b : ";
    cin >> b;

    cout << endl << "Your key is : (" << a <<"," << b <<")" << endl;
    return make_tuple(a, b);
}


int get_way_affine() {
    string way;
    do {
        cout << "Please specify if it is an encryption (1) or a decryption (0) : ";
        cin >> way;
        cout << endl;
    } while (way != "1" && way != "0");

    return stoi(way);
}


string affine_encrypt(string content, int a, int b) {

    int char_val, new_char_val, offset;
    string new_content, new_char;
    for (int i = 0; i < content.length(); i++) {
        char_val = int(content[i]);

        if (char_val != 32) {
            new_char_val = (((a * (char_val - beggin_ascii)) + b ) % ((end_ascii - beggin_ascii) + 1)) + beggin_ascii;
            new_char = char(new_char_val);
        }
        else {
            new_char = " ";
        }
        new_content += new_char;
    }
    return new_content;
}


string affine_decrypt(string content, int a, int b) {

    int diff_ascii = (end_ascii - beggin_ascii) + 1;

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
            new_content = new_content + char(((a_inverse * ((diff_ascii + char_val - beggin_ascii - b)) % diff_ascii)) + beggin_ascii);
        }
        else {
            new_content += " ";
        }     
    }
    return new_content;
}


string affine_main(string content) {

    int way;
    way = get_way_affine();

    int a,b;
    tie(a, b) = get_coefficients_affine();

    string new_content;
    if (way == 1) {
        new_content = affine_encrypt(content, a, b);
    }
    else {
        new_content = affine_decrypt(content, a, b);
    }
    return new_content;
}