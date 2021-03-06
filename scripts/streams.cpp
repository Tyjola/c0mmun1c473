#include <iostream>
#include <fstream>
#include <string.h>

#include "streams.h"

using namespace std;


// open the file to treat and catch the content.
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
        cout << "The file might be missing." << endl << endl;
        return "#####error#####";
    }

    return content;
}


// Create the file containing the encrypted/decrypted content.
int fcreate(string filename, string content) {
    ofstream stream_file("./"+filename);

    if (stream_file) {
        stream_file << content << endl;
        stream_file.close();
        return 1;
    }
    else {
        return 0;
    }
}