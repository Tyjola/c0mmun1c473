#include <iostream>
#include <fstream>
#include <string>

using namespace std;


string fopen(string filename)
{
    string content;
    ifstream stream_file("./"+filename);
    
    if (stream_file)
    {
        string line;
        while (getline(stream_file, line))
        {
            content += line;
        }
    }

    else
    {
        cout << "Problème lors de l'ouverture." << endl;
    }
    
    return content;
}


int main()
{   
    string filename, content;
    cout << "Entrez le nom du fichier à chiffrer : ";
    cin >> filename;

    content = fopen(filename);
    cout << "Le contenu à chiffrer est :" << endl << content << endl;
}

