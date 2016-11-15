#include "LocalitySensitive.hh"

using namespace std;

bool bandBool = true;

LocalitySensitive::LocalitySensitive(const vector<string*>& files, unsigned int k, unsigned int t, unsigned int band, unsigned int modBuckets) {
  fillMatrix(files);
  this->k = k;
  this->t = t;
  this->band = band;
  this->modBuckets = modBuckets;
  unsigned int rows = files.size() / band;
  this->threshold = pow((double) 1/band, (double) 1/rows);
  cout << threshold << endl;
}





void LocalitySensitive::fillMatrix(const vector<string*>& files){
  JaccApprox ja(k,t,files);
  vector<vector<unsigned int> > matriu(files.size(),vector<unsigned int>(files.size(),0.0));
  matrix = matriu;
  ja.obtainSignaturesMatrix(matrix);
  if(matrix.size()% band != 0) {
    cout << " > El nombre de bands no es correcte, ha de ser divisor de: " << matrix.size() << endl;
    bandBool = false;
  }
  vector<vector<bool> > b(files.size(), vector<bool>(files.size(), false));
  marcats = b;
}


unsigned int LocalitySensitive::hashFunction(const vector<unsigned int>& vec){
   unsigned int num = 0.0;
   for(int i = 0; i < vec.size(); ++i) num += vec[i];    
   return fmod(num,modBuckets);
}

void LocalitySensitive::fillColumn(vector<unsigned int>& col, int i, int z){
  int x = 0;
  for(int j = i; j < col.size(); ++j){
    col[x] = matrix[j][z];
    ++x;
  }
}
  
// Pre: band és divisor de la mida de files de la matriu de signatures.
void LocalitySensitive::getBuckets(){
  int n = matrix.size();
  int m = matrix[0].size();
  
  int rows = n / band;
  
  vector<vector<unsigned int> > new_buckets(band, vector<unsigned int>(m, 0.0));
  buckets = new_buckets;
  
  vector<unsigned int> column(rows);
  
  int j = 0;
  for(int b = 0; b < band; b += rows){ // recorrer les "files" -> les bands.
    for(int i = 0; i < m; ++i){  // recorrer les columnes de cada band.
      fillColumn(column, b, i);
      buckets[j][i] = hashFunction(column);
    }
    ++j;
  }
}

bool LocalitySensitive::afegirCandidat(int i, int j){
    double fraccio = 0.0;
    double mida = (double) matrix.size();
    for(int x = 0; x < mida; ++x){
        if(matrix[x][i] == matrix[x][j]) {
            ++fraccio;
        }
    }
   // cout << fraccio/mida << endl;
    if((fraccio/mida) >= threshold) return true;
    return false;
}

void LocalitySensitive::getCandidates(map<int, list<int> >& documents){
  if(bandBool){
  getBuckets();
  int n = buckets.size();
  int m = buckets[0].size();
    for(int i = 0; i < n; ++i){
      for(int j = 0; j < m; ++j){
        unsigned int value = buckets[i][j];
        for(int x = j+1; x < m; ++x){
            unsigned int value2 = buckets[i][x];
            if(not marcats[j][x] and value == value2) {
                if(afegirCandidat(x, j)){
                    documents[j].push_back(x);
                    marcats[j][x] = true;
                    marcats[x][j] = true;
                    //documents[x].push_back(j);
                }
            }
        }
      }
    }
  }
}


void LocalitySensitive::printCandidates(){
  if(bandBool) {
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
}

