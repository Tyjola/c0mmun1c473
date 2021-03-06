#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <sstream>
#include <cmath>

#include "key.h"
#include "DES.h"

using namespace std;

string final_keys[16];
string key;

//Le sous-programme pourr générer des déplacements ciruclaires vers la gauche, selon le nombre voulu
string shiftLeft(int nbrShift, string keyPart) {
    std::string resultKey;
    int const tailleDemi(28);
    //On vérifie si on doit faire un shift de un ou de deux
    if (nbrShift==1) {
        for (int k=1;k<tailleDemi;k++) {
            resultKey+=keyPart[k];
        }
        resultKey+=keyPart[0];
        return resultKey;
    }
    else {
        string tempShift = keyPart;
        for(int i = 0; i < 2; i++){ 
            for(int j = 1; j < tailleDemi; j++){ 
                resultKey += tempShift[j]; 
            } 
            resultKey += tempShift[0]; 
            tempShift = resultKey; 
            resultKey = ""; 
        }
        resultKey = tempShift; 
    }
    return resultKey;
};

void generate_subkeys(string key) {
    //Il s'agit de la première table pour la permutation
    int const taillepc1(56);
    int pc1[taillepc1] = {
	    57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4
        };
    //On effectue la première permutation de la clé de base à l'aide de PC1
    string temp_key1;
    for (int k=0;k<taillepc1;k++) {
        temp_key1+=key[pc1[k]-1];
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
            temp_key21 = shiftLeft(1,temp_key21);
            temp_key22 = shiftLeft(1,temp_key22);
        }
        //sinon de 2 vers la gauche
        else {
            temp_key21 = shiftLeft(2,temp_key21);
            temp_key22 = shiftLeft(2,temp_key22);
        }
        //On redombine ensuite
        string temp_key2 = temp_key21 + temp_key22;
        string finalKeyPart;
        //Enfin, on repermute à l'aide la table PC2 plus courte
        for (int j = 0;j<taillepc2;j++) {
            finalKeyPart+=temp_key2[pc2[j]-1];
        }
        //Et on ajoute cette nouvelle sous-clé terminée à la série de clé finale
        final_keys[i]=finalKeyPart;
        cout << "final_key: " << finalKeyPart<< endl;

    }
};

string calculXOR(string element1, string element2) {
    string xorString;
    int sizeString = element2.size();
    for (int k=0;k<sizeString;k++) {
        if (element1[k] != element2[k]) {
            xorString.append("1");
        }
        else {
            xorString.append("0");
        }
    }
    return xorString;
}

//On utiliser ici la méthode du doublement: res = 2*res + int(binaire[i])
int convertisseurBinaireVersDecimal(string binaire) {
    int resultat;
    int const taille = binaire.size();
    for (int k=0;k<taille;k++) {
        if (binaire[k]=='1') {
            //resultat = 2*resultat + 1;
            resultat += pow(2,taille-k-1);
        }
        else {
            //resultat = 2*resultat;
        }
    }
    return resultat;
};

string convertisseurDecimalVersBinaire(int decimal) {
    string resultat;
    int temp = decimal;
    while (temp !=0) {
        if (temp %2 == 0) {
            resultat = "0" + resultat;
        }
        else {
            resultat = "1" +  resultat;
        }
        temp=temp/2;
    }
    while (resultat.size()<4) {
        resultat = "0" + resultat;
    }
    return resultat;
}

string encyrption_DES(string subkeys[16], string content) {
    //On définit le resultat
    string resultat;
    //On commence avec la permutation initiale de 64 bits
    int const tailleIP(64);
    int IP[tailleIP] = {
    58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7
    };
    std::string keyTemp;
    for (int k=0;k<tailleIP;k++) {
        keyTemp+= content[IP[k]-1];
    }
    //On redivise ce résultat en deux moitiés de 32 bit
    string leftTemp = keyTemp.substr(0,32);
    string rightTemp = keyTemp.substr(32,32);
    //On définit ensuite la table d'expansion qui va permettre d'effectuer le cryptage
    int const tailleET(48);
    int ET[tailleET] = { 
	32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17, 16,17,18,19,20,21,20,21, 22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1 
	};
    //On définit ensuite la table SB qui classifie les différents Si allant de 1 à 8
    int SB[8][4][16]= {
        { 
        14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7, 0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8, 4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0, 15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 
        }, 
        { 
        15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10, 3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5, 0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15, 13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 
        }, 
        { 
        10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8, 13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1, 13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7, 1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 
        }, 
        { 
        7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15, 13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9, 10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4, 3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 
        }, 
        { 
        2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9, 14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6, 4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14, 11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 
        }, 
        { 
        12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11, 10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8, 9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6, 4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 
        }, 
        { 
        4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1, 13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6, 1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2, 6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 
        }, 
        { 
        13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7, 1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2, 7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8, 2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 
        }
    };
    //On définit ensuite une table de permutation pour le  côté droit transformé de 32bit (voir plus-bas)
    int P[32] = { 
        16,7,20,21,29,12,28,17, 1,15,23,26,5,18,31,10, 2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25 
	    };
    //On définit enfin une table IP2 pour effectuer la permutation sur le nouvel élément de 64 bit
    int IP2[64]= { 
        40,8,48,16,56,24,64,32, 39,7,47,15,55,23,63,31, 38,6,46,14,54,22,62,30, 37,5,45,13,53,21,61,29, 36,4,44,12,52,20,60,28, 35,3,43,11,51,19,59,27, 34,2,42,10,50,18,58,26, 33,1,41,9,49,17,57,25 
	    };
    //On passe ensuite au cryptage à proprement parler, qui va s'effectuer 16 fois
    for (int i = 0;i<16;i++) {
        //Pour chaque itération, on va d'abord chercher à calculer la fonction f avant d'effectuer le XOR
        //Pour cela, on définit un élément droit étendu qui sera de 48 bit au lieu de 32
        string rightTempExtended;
        //Ici on va utiliser la table ET pour définir le j-ième de cette version étendue
        for (int j = 0;j<tailleET;j++) {
            rightTempExtended+= rightTemp[ET[j]-1];
            }
        //Maintenant que c'est fait, on va effectuer un XOR sur cette clé étendue avec la ième sous-clé créée avec le programme précédent
        string tempXOR = calculXOR(subkeys[i],rightTempExtended);
        //On va ensuite chercher à transformer les 48 bits à nouveau en 32
        //On définit en premier lieu le string qui fera office de fonction f finale avant le deuxième XOR
        string tempFunction;
        //Ensuite, on va séparer le XOR de 48 bits en 6 string de 8 bits
        for (int l = 0;l<8;l++) {
            //Ceux ci-fonctionnent de la manière suivante: le premier et dernier bit de chaque morceau servent à définir un nombre binaire de 2 bits transformer en entier de 0 à 3,
            //qui donne la ligne de l'élément de substitution
            string cleLigne = tempXOR.substr(6*l,1)+tempXOR.substr(6*l+5,1);
            int cleLigneDecimal = convertisseurBinaireVersDecimal(cleLigne);
            //Quand aux 4 autres, il serviront de nombre binaire de 4 bits à transformer en décimal de 1 à 15, qui donneront sur quelle colonne prendre l'élément de substitution
            string cleColonne = tempXOR.substr(6*l+1,4);
            int cleColonneDecimal = convertisseurBinaireVersDecimal(cleColonne);
            //On récupère l'élement en question sous forme décimale et on le repasse en binaire
            int substDecimal = SB[l][cleLigneDecimal][cleColonneDecimal];
            string substBinaire = convertisseurDecimalVersBinaire(substDecimal);
            //On rajoute ensuite le nouvel élément binaire de 4 bits dans la future fonction f de 32 bits
            tempFunction += substBinaire;
        }
        //On effectue ensuite une nouvelle permutation à l'aide de la table P
        string keyTemp2;
        for (int m=0;m<(tailleIP/2);m++) {
            keyTemp2 += tempFunction[P[m]-1];
        }
        //On effectue ensuite le XOR avec le côté gauche pour obtenir le futur "nouveau" côté droit
        tempXOR =  calculXOR(leftTemp,keyTemp2);
        //enfin, si on en est pas à l'itération finale, on met en place le i+1ème côté gauche et droit pour pouvoir réitérer
        leftTemp = tempXOR;
        if (i<15) {
        string temp = rightTemp;
        leftTemp = temp;            //On a bien L(i+1)=R(i)
        rightTemp = tempXOR;        //On a bien R(i+1)= XOR(L(i),f(...))
        }
    }
    //Une fois à la dernière étape, on fusionne les deux string en commencant par le côté droit
    string tempFinal = leftTemp+rightTemp;
    //On effectue ensuite la permutation finale avec la table IP2
    for (int n=0;n<tailleIP;n++) {
        resultat += tempFinal[IP2[n]-1];
    }
    //On retourne le string crypté
    return resultat;
};

//Le décryptage fonctionne come le cryptage mais en inversant l'ordre des sous-clés
string decryption_DES(string subkeys[16], string crypted_content) {
    int const tailleCle(16);
    string newSubKeys[tailleCle];
    string resultat;
    for (int k=0;k<(tailleCle/2);k++) {
        newSubKeys[k]=subkeys[tailleCle-k-1];
        newSubKeys[tailleCle-k-1]=subkeys[k];
    }
    resultat = encyrption_DES(newSubKeys, crypted_content);
    return resultat;
};

//Pour convertir le texte en binaire 
string convert_text_binary(string text_key) {

    string binary_text, binary;
    for (int i = 0; i < text_key.length(); i++) {
        binary = bitset<8>(int(text_key[i])).to_string();
        binary_text += binary;
    }
    return binary_text;
}

string convert_binary_text(string binary_key) {
    string data = binary_key;
    stringstream sstream(data);
    string text_output;
    while(sstream.good())
    {
        bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        text_output += c;
    }

    return text_output;
}

string DES_main(string content, int start_ascii, int end_ascii, int way) {

    vector<string> char_key{ "0", "1" };
    cout << "debut" <<endl;
    key = key_main(way, "text", 64, start_ascii, end_ascii, char_key);
    string content_binary;
    if(way == 1) {
    // On convertit le texte au format binaire si on est dans la phase de cryptage
    content_binary = convert_text_binary(content);
    cout << "Le texte d'origine, v. binaire: " << content_binary << endl;
    cout << "taille divise par 64: " << (content_binary.size()/64) << endl;
    }
    else {
        //Sinon on récupère juste le texte déjà au format binaire
        content_binary = content;
    }
    // On récupère le multiple de 64 nécessaire pour créer les blocs
    int const debutZeros(content_binary.size()%64);
    int blocs = content_binary.size()/64;
    string sous_blocs[blocs+1];
    //On divise tous les blocs sauf le dernier en sous-blocs de 64 bits
    for (int k=0;k<blocs;k++) {
        sous_blocs[k]=content_binary.substr(64*k,64);
    }
    //Pour le dernier blocs, on récupère ce qu'il reste et on rajoute des 0 pour compléter
    string tempBlocFinal=content_binary.substr(64*blocs,debutZeros);
    cout << "taille Actuelle: " << tempBlocFinal.size() << endl;
    for (int i = debutZeros;i<64;i++) {
        tempBlocFinal += "0";
    }
    //On vérifie si il y a un problème
    sous_blocs[blocs]=tempBlocFinal;
    if (tempBlocFinal.size() != 64) {
        cout << "taille bloc final :" << tempBlocFinal.size() << endl;
        cout << "Problème de blocs dans le texte" << endl;
        return 0;
    }
    int const nombreBlocs(blocs+1);
    //On génère les sous-clés dans final_keys
    generate_subkeys(key);
    if(way == 1) {
        string texteCrypte;
        //Pour chaque bloc, on utilise les sous-clés pour le cryptage et on récupère un texte crypté
        for (int j=0;j<nombreBlocs;j++) {
            string tempPart = encyrption_DES(final_keys,sous_blocs[j]);
            texteCrypte += tempPart;
        }
        cout << "Ceci est le texte crypte: " << texteCrypte << endl << endl;
        return texteCrypte;
    }
    else {
        //Si décyptage
        string texteRestitue;
        int const tailleCle(16);
        string newSubKeys[tailleCle];
        //On inverse les sous-clés
        for (int k=0;k<(tailleCle/2);k++) {
            newSubKeys[k]=final_keys[tailleCle-k-1];
            newSubKeys[tailleCle-k-1]=final_keys[k];
            cout << "final_key modifiée: " << newSubKeys[k] << endl;
        }
        //On décrypte ensuite chaque bloc
        for (int l=0;l<nombreBlocs;l++) {
            string tempPart = encyrption_DES(newSubKeys,sous_blocs[l]);
            texteRestitue += tempPart;
        }
        cout << "Texte Restitué en binaire :" << texteRestitue << endl << endl;
        //On enlève ensuite les 0 inutiles à la fin du dernier bloc en utilisant le nombre "debutZeros" défini au début
        string texteRetourFinal = texteRestitue.substr(0,64*blocs+debutZeros-1);
        cout << "Modulo 64: " << (texteRestitue.size()%64) << endl;
        //Il reste à re-traduire le binaire en texte
        cout << "Texte Restitué :" << texteRetourFinal << endl;
        cout << "taille divise par 64: " << (texteRetourFinal.size()/64) << endl;
        return texteRetourFinal;
    }
};