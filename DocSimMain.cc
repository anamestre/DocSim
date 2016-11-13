#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

void loadPaths (string path, int num, vector<string>& paths) {
    paths = vector<string>(num);
    for (int i = 1; i <= num; ++i) {
        paths[i] = path;
        paths[i] += "/doc";
        paths[i] += i;
    }
}

void loadDoc(int num, string& doc, const vector<string>& paths) {
    ifstream file;
    file.open(paths[num].c_str());
    if (file.is_open()) {
        file.seekg(0, file.end);
        int length = file.tellg();
        file.seekg(0, file.beg);

        char* readFile = new char [length];
        file.read(readFile, length);
        doc = readFile;
        file.close();
    }
}


void showMenu() {
    cout << "Selecciona una operació:" << endl;
    cout << "-1: Similitud de Jaccard per dos documents" << endl;
    cout << "-2: Aproximació de la similitud de Jaccard mitjançant signatures minhash" << endl;
    cout << "-3: Ús de l'algorisme LSH pel càlcul de similituds" << endl;
    cout << "-4: Càrrega de documents" << endl;
    cout << "99: Sortir"<< endl;
}

int main() {
    int ops;
    vector<string> paths;
    cout << "DocSim" << endl;
    showMenu();
    cin >> ops;
    while(ops != 99) {
        if (ops == -1) {
            //Integrar i tal
        }
        else if (ops == -2 ) {

        }
        else if (ops == -3) {

        }
        else if (ops == -4) {
            cout << "Introdueix el camí a la carpeta que conté els documents:" << endl;
            string path;
            cin >> path;
            cout << "Introdueix el número de documents:" << endl;
            int num;
            cin >> num;
            loadPaths(path, num, paths);
            cout << "Càrrega completada" << endl;
        }
        else {
            cout << "L'operació no existeix" << endl;
        }
        cout << "-------" << endl;
        showMenu();
        cin >> ops;
    }

}