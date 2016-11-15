
#ifndef LOCALITYSENSITIVE_HH
#define LOCALITYSENSITIVE_H

#include <iostream>
#include <string>
#include <map>
#include "JaccApprox.hh"
#include <list>
#include <vector>
#include <cmath>
using namespace std;



class LocalitySensitive {
  public:  
    LocalitySensitive(const vector<string*>& files, unsigned int k, unsigned int t, unsigned int band, unsigned int modBuckets);
    void getCandidates(map<int, list<int> >& documents);
    void printCandidates();
  
  private:
    unsigned int k, t, band, modBuckets;
    double threshold;
    vector<vector<unsigned int> > buckets;
    vector<vector<unsigned int> > matrix;
    vector<vector<bool> > marcats;

    void fillMatrix(const vector<string*>& files);
    unsigned int hashFunction(const vector<unsigned int>& vec);
    void fillColumn(vector<unsigned int>& col, int i, int z);
    void getBuckets();
    bool afegirCandidat(int i, int j);

};

#endif
