#include <iostream>
#include <string>

#include "key.h"

using namespace std;




int DES_main(string content, int way) {
    string subkeys[16];
    string key = key_main(way, "text");
    cout << "The key is : " << key << endl << endl; 
    return 1;
};

string generate_subkeys(string key) {
    string final_key[16];
    //Il s'agit de la première table pour la permutation
    int const taillepc1(56);
    int pc1[taillepc1] = {
	57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4
    };
    //On effectue la première permutation de la clé de base à l'aide de PC1
    string temp_key1;
    for (int k=0;k<taillepc1;k++) {
        temp_key1.append(key[pc1[k]-1]);
    }
    //On sépare ensuite cette première clé en deux moitié de 28 éléments
    string temp_key21 = temp_key1.substr(0,28);
    string temp_key22 = temp_key1.substr(28,28);
};
