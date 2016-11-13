//#include "LocalitySensitive.hh"
#include "JaccApprox.hh"
#include <set>
#include <vector>
#include <map>
#include <list>
#include <cmath>
using namespace std;

vector<vector<double> > buckets;
vector<vector<double> > matrix;
vector<vector<bool> > marcats;


void fillMatrix(const vector<string*>& files, int k, int t){
  JaccApprox ja(k,t,files);
  vector<vector<double> > matriu(files.size(),vector<double>(files.size(),0.0));
  matrix = matriu;
  ja.obtainJaccardApproximation(matrix);
  vector<vector<bool> > b(files.size(), vector<bool>(files.size(), false));
  marcats = b;
}


double hashFunction(const vector<double>& vec, int mod){
   double num = 0.0;
   for(int i = 0; i < vec.size(); ++i) num += vec[i];    
   return fmod(num,mod);
}

void fillColumn(vector<double>& col, int i, int z){
  int x = 0;
  for(int j = i; j < col.size(); ++j){
    col[x] = matrix[j][z];
    ++x;
  }
}
  
// Pre: band és divisor de la mida de la matriu de signatures.
void getBuckets(int band, double modBuckets){
  int n = matrix.size();
  int m = matrix[0].size();
  
  int rows = n / band;
  
  vector<vector<double> > new_buckets(band, vector<double>(m, 0.0));
  buckets = new_buckets;
  
  vector<double> column(rows);
  
  int j = 0;
  for(int b = 0; b < band; b += rows){ // recorrer les "files" -> les bands.
    for(int i = 0; i < m; ++i){  // recorrer les columnes de cada band.
      fillColumn(column, b, i);
      buckets[j][i] = hashFunction(column, modBuckets);
    }
    ++j;
  }
}

void getCandidates(map<int, list<int> >& documents){
  int n = buckets.size();
  int m = buckets[0].size();
    for(int i = 0; i < n; ++i){
      for(int j = 0; j < m; ++j){
	  double value = buckets[i][j];
	  for(int x = j+1; x < m; ++x){
	    double value2 = buckets[i][x];
	    if(value == value2 and not marcats[j][x]) {
	      documents[j].push_back(x);
	      marcats[j][x] = true;
	      marcats[x][j] = true;
	      //documents[x].push_back(j);
	    }
	  }
      }
    }
}

void printCandidates(){
  map<int, list<int> > documents;
  getCandidates(documents);
  map<int, list<int> > :: iterator it;
  list <int> :: iterator it2;
  
  cout << "Documents candidats a ser similars" << endl;
  for(it = documents.begin(); it != documents.end(); ++it){
    for(it2 = it->second.begin(); it2 != it->second.end(); ++it2){
      cout << it->first << " i "  << *it2 << endl;
    }
  }
}
  

int main(){
  string file1 = "En el caso de que su baja se prolonga other siiiiiise hasta 2017, el alemán no estará en Mestalla contra el Valencia, encuentro de Liga tras la disputa del Mundial de Clubes, que finaliza el 18 de diciembre.";
  string file2 = "alemán adio José Alvalade (5ª jornad other siiiiiia de la fase de grupos de la Champions), Spotural Leonesa (vuelta de la Copa del Rey), El Clásico ante el Barcelona en el Camp Nou, Borussia Dortmund en el Santiago Bernabéu (6ª y última jornada de la fase de grupos de la Champions) y Deportivo de la Coruña.En el caso de que su baja se prolongase hasta 2017, el alemán no estará en Mestalla contra el Valencia, encuentro de Liga tras la disputa del Mundial de Clubes, que finaliza el 18 de diciembre.";
  string file3 = "Heeeeeeeello from the other siiiiiiide";
  string file4 = "parapjsgnsjgfgfdhdfljg other siiiiii";
  int k, t, band, modBuckets;
  cout << "Insereix k, t, nombre de bands i nombre de buckets: " << endl;
  cin >> k >> t >> band >> modBuckets;
  
  vector<string* > files;
  files.push_back(&file1);
  files.push_back(&file2);
  files.push_back(&file3);
  files.push_back(&file4);
  
  fillMatrix(files, k, t);
  getBuckets(band, modBuckets);
  printCandidates();
  
}

