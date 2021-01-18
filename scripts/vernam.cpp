#include <iostream>
#include <string>

#include "vernam.h"
#include "key.h"

using namespace std;


string vernam_encrypt(string content, int way, string key, int start_ascii, int end_ascii) {

    int key_length = key.length();
    
    int char_val, new_char_val, offset;
    string new_content, new_char;
    for (int i = 0; i < content.length(); i++) {
        //On récupère la valeur du charactère
        char_val = int(content[i]);

        if (char_val != 32) {
            offset = int(key[i]) - start_ascii;
            if (way == 0) { offset = offset * -1; }
            //On fait la somme entre la valeur [i] de la clé/du masque et du texte à coder
            new_char_val = char_val + offset;

            //Ces deux lignes ervent d'équivalent du modulo 26 : si on sort des limites de l'ascii on retourne dedans 
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

string vernam_main(string content, int start_ascii, int end_ascii, int way) {
    
    string key;
    int key_length = content.length();
    vector<string> char_key = {};
    key = key_main(way, "text", key_length, start_ascii, end_ascii, char_key);
    
    string new_content;
    new_content = vernam_encrypt(content, way, key, start_ascii, end_ascii);

    return new_content;
}