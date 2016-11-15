#ifndef JACCAPPROX_HH
#define JACCAPPROX_HH

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

struct HashValues {
  unsigned int hash_1;
  unsigned int hash_2;
};

class JaccApprox {
  public:
    JaccApprox(unsigned int k, unsigned int t, vector<string*> mFiles);
    void obtainJaccardApproximation(vector<vector<double> >& result);
    void obtainSignaturesMatrix(vector<vector<unsigned int> >& result);
  private:
      unsigned int t; // number of hash functions used
      unsigned int k; // size of the shingles
      vector<string*> mFiles;
      void computeSignatures(vector<unsigned int>& signatures);
      void updateSimValues(const vector<unsigned int>& signatures, vector<vector<double> >& result);
      double valueToUptate; // Value to sum when there is a match
      HashValues mHV;
      unsigned int maxIntHash; // used in the computation of the hash
      vector<unsigned int> bigPrimesVector;
      unsigned int bigPrime();
      unsigned int hashFromShingle(const string& shingle);
      void getNewHashValues();
      unsigned int minhashSignature(string* mFile);
};

#endif
