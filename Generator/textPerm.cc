#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <cstdio>
using namespace std;

int contPerm;
int numPerm;

void mostra(const vector<string>& perm) {
   ++contPerm;
   if (contPerm > numPerm) exit(0);
   else {
     string name="file_" + to_string(contPerm) + ".txt";
     ofstream fs(name);
      for (int i = 0; i < perm.size(); ++i) {
  	     fs << perm[i] <<endl;
  	  }
      fs.close();
    }
}

void permuta(vector<string>& perm, int i, vector< pair<string,bool> >& presents) {
  if (i == perm.size()) {
    mostra(perm);
  }
  else {
    for (int k = 0; k < presents.size(); ++k) {
      if (not presents[k].second) {
      	perm[i] = presents[k].first;
      	presents[k].second = true;
      	permuta(perm,i+1,presents);
      	presents[k].second = false;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cout << "Usage: ./textPerm N (nombre de permutacions que es vol obtenir)" << endl;
    exit(1);
  }
  numPerm = atoi(argv[1]);
  vector< pair<string,bool> > presents;
  string paraula;
  int numParaules = 0;
  while(cin >> paraula) {
    char last = paraula[paraula.size()-1];
    if (last == '.' or last == ',' or last == ';' or last == ':') { //Clean punctuation
       paraula = paraula.substr(0,paraula.size()-1);
    }
    ++numParaules;
    pair<string,bool> p;
    p.first = paraula;
    p.second = false;
    presents.push_back(p);
  }
  contPerm = 0;
  vector<string> perm(numParaules);
  permuta(perm,0,presents);
}
