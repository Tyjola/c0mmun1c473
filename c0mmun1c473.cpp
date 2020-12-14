#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;


string fopen(string filename) {
    string content;
    ifstream stream_file("./"+filename);
    
    if (stream_file) {
        string line;
        while (getline(stream_file, line)) {
            content += line;
        }
    }

    else {
        cout << "There is a problem with the file opening." << endl;
    }

    return content;
}


int fcreate(string filename, string content) {
    ofstream stream_file("./"+filename);
    stream_file << content << endl;
    stream_file.close();
    return 0;
}


string caesar_ciffer(string content) {   
    int offset;
    cout << "Indicate the offset for Caesar's encryption : ";
    cin >> offset;

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


int main(int argc, char *argv[]) {   

    string filename, new_filename, state;
    for (int i = 1; i < argc; i++) {   
        if (i + 1 != argc) {   
            string arg = argv[i];

            // Specifies the name of the file to encrypt.
            if (arg == "-f") {
                filename = argv[i+1];
            }
            // Specifies the name of the file encrypted.
            if (arg == "-o") {
                new_filename = argv[i+1];
            }
        }
    }

    string content, new_content;

    content = fopen(filename);
    new_content = caesar_ciffer(content);

    fcreate(new_filename, new_content);
    cout << "Encryption has been performed correctly." << endl;
}

