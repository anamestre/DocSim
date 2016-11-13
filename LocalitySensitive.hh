
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
    LocalitySensitive(const vector<string*>& files, int k, int t, int band, int modBuckets);
    void getCandidates(map<int, list<int> >& documents);
    void printCandidates();
  
  private:
    int k, t, band, modBuckets;
    double threshold;
    vector<vector<double> > buckets;
    vector<vector<double> > matrix;
    vector<vector<bool> > marcats;

    void fillMatrix(const vector<string*>& files);
    double hashFunction(const vector<double>& vec);
    void fillColumn(vector<double>& col, int i, int z);
    void getBuckets();

};

#endif