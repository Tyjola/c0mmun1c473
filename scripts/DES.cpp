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
    string final_keys[16];
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
    //On définit les 4 valeurs pour lesquelles on effectuera 1 seul shift
    int lst_shift[4]= {0,1,8,15};
    //On définit aussi la deuxième table PC2 pour pouvoir effectuer les permutations après les shifts
    int const taillepc2(48);
    int pc2[taillepc2] = { 
	    14,17,11,24,1,5, 3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32 
	    };
    //On passe ensuite au gros morceau, la génération des 16 sous-clés
    int const nombreCles(16);
    for (int i=0;i<nombreCles;i++) {
        //Si égal à ces 4 nombres, on effectue un shift ciruclaire de seulement 1 vers la gauche
        if (i==0 || i==1 || i==8 || i==15) {
            temp_key21 = shiftLeft(1,tempKey21);
            temp_key22 = shiftLeft(1,tempKey22);
        }
        //sinon de 2 vers la gauche
        else {
            temp_key21 = shiftLeft(2,tempKey21);
            temp_key22 = shiftLeft(2,tempKey22);
        }
        //On redombine ensuite
        string temp_key2 = temp_key21 + temp_key22;
        string finalKeyPart;
        //Enfin, on repermute à l'aide la table PC2 plus courte
        for (int j = 0;j<taillepc2;j++) {
            finalKeyPart.append(temp_key2[pc2[i]-1]);
        }
        //Et on ajoute cette nouvelle sous-clé terminée à la série de clé finale
        final_keys[i]=finalKeyPart;
    }
};

//Le sous-programme pourr générer des déplacements ciruclaires vers la gauche, selon le nombre voulu
string shiftLeft(int nbrShift, string keyPart) {
    string resultKey;
    int const tailleDemi(28);
    //On vérifie si on doit faire un shift de un ou de deux
    if (nbrShift==1) {
        for (int k=1;k<tailleDemi;k++) {
            resultKey.append(keyPart[k]);
        }
        resultKey.append(keyPart[0]);
        return resultKey;
    }
    else {
        for (int i=2;i<tailleDemi;i++) {
            resultKey.append(keyPart[i]);
        }
        resultKey.append(keyPart[0]);
        resultKey.append(keyPart[1]);
    }
    return resultKey
};
