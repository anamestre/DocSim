#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "JaccApprox.hh"
using namespace std;

void loadPaths (string path, int num, vector<string>& paths) {
    paths = vector<string>(num);
    for (int i = 1; i < num; ++i) {
        paths[i-1] = path;
        paths[i-1] += "doc";
        paths[i-1] += to_string(i);
        paths[i-1] += ".txt";
    }
}

//Retorna cierto si lo ha podido cargar.
bool loadDoc(int num, string& doc, const vector<string>& paths) {
    ifstream file;
    file.open(paths[num].c_str());
    cout << "Path: " << paths[num].c_str() << endl;
    if (file.is_open()) {
        file.seekg(0, file.end);
        int length = file.tellg();
        file.seekg(0, file.beg);
        char* readFile = new char [length];
        file.read(readFile, length);
        doc = readFile;
        file.close();
        return true;
    }
    return false;
}

int getNumOfFiles(string path) {
  DIR *dp;
  int i = 0;
  struct dirent *ep;
  dp = opendir (path.c_str());

  if (dp != NULL) {
    while (ep = readdir (dp)) i++;
    return i-6; //6 archivos necesarios (makefile, codigo fuente.. etc) que no son para procesar
    (void) closedir (dp);
  }
  else return -1;
}

// -------------- FUNCIONES DE DOCSIM 2 ----------------------------------

void getReferencesFromFiles(vector<string>& mFiles, vector<string*>& mFileReferences) {
  for (int i = 0; i < mFiles.size(); ++i)
    mFileReferences.push_back(&mFiles[i]);
}

void mostraResultat(const vector<vector< double > >& matriu) {
  for (int i = 0; i < matriu.size(); ++i) {
    for (int j = 0; j < matriu.size(); ++j) {
      if (i == j) cout << "X ";
      else cout << matriu[i][j] << " ";
    }
    cout << endl;
  }
}

// void readFiles(vector<string>& mFiles) {
//   string file1 = "En el caso de que su baja se prolonga other siiiiiise hasta 2017, el alemán no estará en Mestalla contra el Valencia, encuentro de Liga tras la disputa del Mundial de Clubes, que finaliza el 18 de diciembre.";
//   string file2 = "alemán adio José Alvalade (5ª jornad other siiiiiia de la fase de grupos de la Champions), Spotural Leonesa (vuelta de la Copa del Rey), El Clásico ante el Barcelona en el Camp Nou, Borussia Dortmund en el Santiago Bernabéu (6ª y última jornada de la fase de grupos de la Champions) y Deportivo de la Coruña.En el caso de que su baja se prolongase hasta 2017, el alemán no estará en Mestalla contra el Valencia, encuentro de Liga tras la disputa del Mundial de Clubes, que finaliza el 18 de diciembre.";
//   string file3 = "Heeeeeeeello from the other siiiiiiide";
//   string file4 = "parapjsgnsjgfgfdhdfljg other siiiiii";
//   mFiles.push_back(file1);
//   mFiles.push_back(file3);
//   mFiles.push_back(file2);
//   mFiles.push_back(file4);
// }

bool readFiles(vector<string>& mFiles, const vector<string>& paths) {
  if (paths.size() == 0) {
    cout << "Error: No s'han carregat els paths." << endl;
    return false;
  }
  else {
    bool valid;
    bool totsValids = true;
    for (int i = 1; i < paths.size(); ++i) {
      string doc;
      valid = loadDoc(i,doc,paths);
      if (not valid) {
        cout << "El path del document " << i << " és incorrecte" << endl;
        totsValids = false;
      }
    }
    return totsValids;
  }
  return false;
}

void jaccardApproximation(const vector<string>& paths) {
  unsigned int k = 9; // atoi(argv[1]);
  unsigned int t = 100; // atoi(argv[2]);
  vector<string> mFiles;
  if (readFiles(mFiles,paths)) {
    vector<string*> mFileReferences;
    getReferencesFromFiles(mFiles,mFileReferences);
    JaccApprox mJA(k,t,mFileReferences);
    vector<vector< double > > matriu(mFiles.size(),vector<double>(mFiles.size(),0.0));
    mJA.obtainJaccardApproximation(matriu);
    mostraResultat(matriu);
  }
  else cout << "Els fitxers no s'han llegit correctament." << endl;
}

// ----------------------------------------------

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
          jaccardApproximation(paths);
        }
        else if (ops == -3) {

        }
        else if (ops == -4) {
            // cout << "Introdueix el camí a la carpeta que conté els documents:" << endl;
            // string path;
            // cin >> path;
            // cout << "Introdueix el número de documents:" << endl;
            // int num;
            // cin >> num;

            string path = "./Generator/";
            int num = getNumOfFiles(path);
            cout << "Al directori " << path << " s'han trobat " << num << " fitxers" << endl;
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
