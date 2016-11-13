#include <iostream>
#include <string>
using namespace std;

void loadDocs(string path, int num, vector<string>& docs) {
    docs = vector<string>(num);
    for (int i = 1; i <= num; ++i) {
        docs[i] = path+"/doc"+i;
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
    vector<string> docs;
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
            loadDocs(path, num);
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