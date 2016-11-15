#include "LocalitySensitive.hh"

using namespace std;

LocalitySensitive :: LocalitySensitive(const vector<string*>& files, int k, int t, int band, int modBuckets) {
  fillMatrix(files);
  this->k = k;
  this->t = t;
  this->band = band;
  this->modBuckets = modBuckets;
}


void LocalitySensitive :: fillMatrix(const vector<string*>& files){
  JaccApprox ja(k,t,files);
  vector<vector<double> > matriu(files.size(),vector<double>(files.size(),0.0));
  matrix = matriu;
  ja.obtainJaccardApproximation(matrix);
  vector<vector<bool> > b(files.size(), vector<bool>(files.size(), false));
  marcats = b;
}


double LocalitySensitive :: hashFunction(const vector<double>& vec){
   double num = 0.0;
   for(int i = 0; i < vec.size(); ++i) num += vec[i];    
   return fmod(num,modBuckets);
}

void LocalitySensitive :: fillColumn(vector<double>& col, int i, int z){
  int x = 0;
  for(int j = i; j < col.size(); ++j){
    col[x] = matrix[j][z];
    ++x;
  }
}
  
// Pre: band és divisor de la mida de files de la matriu de signatures.
void LocalitySensitive ::getBuckets(){
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
      buckets[j][i] = hashFunction(column);
    }
    ++j;
  }
}

void LocalitySensitive :: getCandidates(map<int, list<int> >& documents){
  getBuckets();
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


void LocalitySensitive::printCandidates(){
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


