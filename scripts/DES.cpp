#include <iostream>
#include <string>

#include "key.h"

using namespace std;




int DES_main(string content, int way) {

    string key = key_main(way, "text");
    cout << "The key is : " << key << endl << endl; 
    return 1;
};
