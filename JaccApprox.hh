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
    JaccApprox(unsigned int k, unsigned int t, string mFile_1, string mFile_2);



    // void fill(unsigned int k, unsigned int t, const string& mFile_1, const string& mFile_2);
    double obtainJaccardApproximation();
  private:
      unsigned int t; // number of hash functions used
      unsigned int k; // size of the shingles
      string mFile_1;
      string mFile_2;
      HashValues mHV;
      // unsigned int maxIntHash; // used in the computation of the hash
      vector<unsigned int> bigPrimesVector;
      // void inizializePrimesArray();
      unsigned int bigPrime();
      unsigned int hashFromShingle(const string& shingle);
      void getNewHashValues();
      bool sameMinhashSignature();
      unsigned int minhashSignature(const string& mFile);
};

#endif
