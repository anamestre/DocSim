#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctime>
#include <algorithm>
#include "JaccApprox.hh"
#include "parser.h"
#include "LocalitySensitive.hh"
using namespace std;

string path = "./Generator/";

void loadPaths (string path, int num, vector<string>& paths) {
    paths = vector<string>(num);
    for (int i = 1; i <= num; ++i) {
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
    while (ep = readdir(dp)) i++;
    if (path == "./Generator/") return i-5; //. , .. , ejecutable, textToPermute, codigoFuente
    else return i-2; // En caso de CustomDocs, solo son 2 archivos extra (. , ..)
    (void) closedir (dp);
  }
  else return -1;
}

// -------------- FUNCIONS DE DOCSIM 1 --------------------------

set<int> reunion (const set<int>& a, const set<int>& b) {
	set<int> result = a;
	for (set<int>::iterator it=b.begin(); it!=b.end(); ++it) {
        result.insert(*it);
    }
    return result;
}

double jaccard(string pathdoc1, string pathdoc2, int k) {
	clock_t begin = clock();
	set<int> a = parser(pathdoc1, k);
	set<int> b = parser(pathdoc2, k);
	set<int> reunionset = reunion(a, b);
	set<int> intersectionset;
	set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(intersectionset, intersectionset.begin()));
	double jaccardSim = double(intersectionset.size())/double(reunionset.size());
	clock_t end = clock();
	double elapsed_millisecs = double(end - begin) / (CLOCKS_PER_SEC/1000);
	cout << ">> Temps d'execució de l'algorisme: " << elapsed_millisecs << " mil·lisegons" << endl;
	return jaccardSim;

}

// -------------- FUNCIONES DE DOCSIM 2 ----------------------------------

void getReferencesFromFiles(vector<string>& mFiles, vector<string*>& mFileReferences) {
  for (int i = 0; i < mFiles.size(); ++i)
    mFileReferences.push_back(&mFiles[i]);
}

void mostraResultatSimplificat(const vector<vector< double > >& matriu) {
  for (int i = 0; i < matriu.size(); ++i) {
    for (int j = 0; j < matriu.size(); ++j) {
      if (i == j) cout << "X ";
      else cout << matriu[i][j] << " ";
    }
    cout << endl;
  }
}

void mostraResultat(const vector<vector< double > >& matriu) {
  for (int i = 0; i < matriu.size(); ++i) {
    cout << " === Similaritud amb document " << i+1 << " ===" << endl;
    for (int j = 0; j < matriu.size(); ++j) {
      if (i != j) cout << "doc" << j+1 << ": " << matriu[i][j] << " ";
    }
    cout << endl;
  }
}

bool readFiles(vector<string>& mFiles, const vector<string>& paths) {
  if (paths.size() == 0) {
    cout << "Error: No s'han trobat els fitxers. S'han de carregar amb la opcio -4" << endl;
    return false;
  }
  else {
    bool valid;
    bool totsValids = true;
    for (int i = 0; i < paths.size(); ++i) {
      string doc;
      valid = loadDoc(i,doc,paths);
      if (not valid) {
        cout << "El path del document " << i+1 << " és incorrecte" << endl;
        totsValids = false;
      }
      else {
        mFiles[i] = doc;
      }
    }
    return totsValids;
  }
  return false;
}

void jaccardApproximation(const vector<string>& paths, unsigned int k, unsigned int t) {
  clock_t begin = clock();
  vector<string> mFiles(paths.size());
  bool readOK = readFiles(mFiles,paths);
  if (readOK) {
    vector<string*> mFileReferences;
    getReferencesFromFiles(mFiles,mFileReferences);
    JaccApprox mJA(k,t,mFileReferences);
    vector<vector< double > > matriu(mFiles.size(),vector<double>(mFiles.size(),0.0));
    mJA.obtainJaccardApproximation(matriu);
    clock_t end = clock();
    double elapsed_millisecs = double(end - begin) / (CLOCKS_PER_SEC/1000);
    cout << "El temps d'execució de l'algorisme ha estat de " << elapsed_millisecs << " mil·lisegons" << endl;
    cout << "Vols veure el resultat en format compacte o extès? (c/e)" << endl;
    char o;
    cin >> o;
    if (o == 'e') mostraResultat(matriu);
    else if (o != 'c') {
      cout << "Opció no vàlida, es mostrarà compacte" << endl;
      mostraResultatSimplificat(matriu);
    }
    else mostraResultatSimplificat(matriu);
  }
  else cout << "Els fitxers no s'han llegit correctament." << endl;
}

// -------- FUNCIONS DE DOCSIM3 ---------------------------

void calculaLocalitySensitive(const vector<string>& paths, unsigned int k, unsigned int t, unsigned int bands, unsigned int modBuckets){
  vector<string> mFiles(paths.size());
  bool readOK = readFiles(mFiles, paths);
  if(readOK){
      vector<string*> mFileReferences;
      getReferencesFromFiles(mFiles,mFileReferences);
      LocalitySensitive LSH(mFileReferences, k, t, bands, modBuckets);
      LSH.printCandidates();
  }
  else cout << "Els fitxers no s'han llegit correctament." << endl;
}


// ----------------------------------------------

void showMenu(unsigned int k, unsigned int t) {
    cout << "Selecciona una operació:" << endl;
    cout << "-1: Similitud de Jaccard per dos documents" << endl;
    cout << "-2: Aproximació de la similitud de Jaccard mitjançant signatures minhash" << endl;
    cout << "-3: Ús de l'algorisme LSH pel càlcul de similituds" << endl;
    cout << "-4: Càrrega de documents" << endl;
    cout << "-5: Modificar els paràmetres k i t (actualment, "<< k << " i " << t << ", valors per defecte 9 i 100, respectivament)" << endl;
    cout << "99: Sortir"<< endl;
}

int main() {
    int ops;
    unsigned int k, t;
    k = 9;
    t = 100;
    vector<string> paths;
    cout << "======= DocSim =======" << endl;
    showMenu(k,t);
    cin >> ops;
    cout << endl;
    while(ops != 99) {
        if (ops == -1) {
            cout << "> Introdueix els nombres dels dos documents a comparar, separats per un espai" << endl;
            int doc1, doc2;
            cin >> doc1 >> doc2;
            cout << ">> El grau de similitud de Jaccard dels documents és " << jaccard(paths[doc1-1], paths[doc2-1], k) << endl;
        }
        else if (ops == -2 ) {
          jaccardApproximation(paths,k,t);
        }
        else if (ops == -3) {
	  cout << "> Introdueix el nombre de bandes en el qual vols que es divideixi la matriu:" << endl;
	  unsigned int bands, modBuckets;
	  modBuckets = 100;
	  cin >> bands;
	  calculaLocalitySensitive(paths, k, t, bands, modBuckets);

        }
        else if (ops == -4) {
            cout << "Quins documents vols carregar?" << endl;
            cout << "-1 Documents del directori Generator (permutacions del mateix document)" << endl;
            cout << "-2 Documents del directori CustomDocs (documents qualssevol afegits per l'usuari)" << endl;
            int option;
            bool validOption = true;
            cin >> option;
            switch (option) {
              case -1:
                path = "./Generator/";
                break;
              case -2:
                path = "./CustomDocs/";
                break;
              default:
              validOption = false;
                cout << "La opció escollida es invàlida" << endl;
                break;
            }
            if (validOption) {
              int num = getNumOfFiles(path);
              cout << "Al directori " << path << " s'han trobat " << num << " fitxers" << endl;
              loadPaths(path, num, paths);
              cout << "Càrrega completada" << endl;
          }
        }
        else if (ops == -5) {
          cout << "Si us plau, entra els valors de k i t, separats per un espai" << endl;
          cin >> k >> t;
          cout << "Els valors de k i t s'han actualitzat a " << k << " i " << t << " respectivament." << endl;
        }
        else {
            cout << "L'operació no existeix" << endl;
        }
        cout << "------------------------------------------" << endl;
        showMenu(k,t);
        cin >> ops;
        cout << endl;
    }

}
