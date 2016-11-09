#ifndef JACCAPPROX_HH
#define JACCAPPROX_HH

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

struct HashValues {
  unsigned int hash_1;
  unsigned int hash_2;
};

class JaccApprox {
  public:
    JaccApprox(unsigned int k, unsigned int t, vector<string*> mFiles);
    vector<vector<double> > obtainJaccardApproximation();
  private:
      unsigned int t; // number of hash functions used
      unsigned int k; // size of the shingles
      vector<string*> mFiles;

      vector<vector<double> > SimMat;
      void computeSignatures(vector<unsigned int>& signatures);
      void updateSimValues(const vector<unsigned int>& signatures);
      double valueToUptate;


      HashValues mHV;
      unsigned int maxIntHash; // used in the computation of the hash
      vector<unsigned int> bigPrimesVector;
      unsigned int bigPrime();
      unsigned int hashFromShingle(const string& shingle);
      void getNewHashValues();
      // bool sameMinhashSignature();
      unsigned int minhashSignature(string* mFile);
};

#endif
