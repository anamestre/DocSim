#include "JaccApprox.hh"
using namespace std;

JaccApprox::JaccApprox(unsigned int k, unsigned int t, vector<string*> mFiles) {
  this->k = k;
  this->t = t;
  this->mFiles = mFiles;

  valueToUptate = double(1)/double(t); // Value to sum when there is a match

  JaccApprox::bigPrimesVector = {547,563,733,619,691,829,911,701,599,601,827,659};
  maxIntHash = 0x11111111;
}

unsigned int JaccApprox::hashFromShingle(const string& shingle) {
  unsigned int a, b;
  a = mHV.hash_1;
  b = mHV.hash_2;
  for (unsigned int i = 0; i < shingle.length(); ++i) {
    a = (a*b) + shingle[i];
  }
  return a%(maxIntHash);
}

unsigned int JaccApprox::minhashSignature(string* mFilePointer) {
  string mFile = *mFilePointer;
  if (mFile.length() < k) return hashFromShingle(mFile);
  unsigned int minimumHash = hashFromShingle(mFile.substr(0,k));
  for (unsigned int i = 1; i <= mFile.length() - k; ++i) {
    unsigned int hashAtCurrentPosition = hashFromShingle(mFile.substr(i,k));
    if (hashAtCurrentPosition < minimumHash) minimumHash = hashAtCurrentPosition;
  }
  return minimumHash;
}


unsigned int JaccApprox::bigPrime() {
  return bigPrimesVector[rand()%bigPrimesVector.size()];
}

void JaccApprox::getNewHashValues() {
  mHV.hash_1 = rand()%bigPrime();
  mHV.hash_2 = rand()%bigPrime();
}

void JaccApprox::computeSignatures(vector<unsigned int>& signatures) {
  for (unsigned int i = 0; i < signatures.size(); ++i) {
    signatures[i] = minhashSignature(mFiles[i]);
  }
}

void JaccApprox::updateSimValues(const vector<unsigned int>& signatures, vector<vector<double> >& result) {
  for (unsigned int i = 0; i < signatures.size(); ++i) {
    unsigned int aux = signatures[i];
    for (unsigned int j = 0; j < signatures.size(); ++j) {
      if (i != j and aux == signatures[j]) {
        result[i][j] += valueToUptate;
      }
    }
  }
}

void JaccApprox::obtainJaccardApproximation(vector<vector<double> >& result) {
  vector<unsigned int> signatures(mFiles.size());
  for (unsigned int i = 0; i < t; ++i) {
    getNewHashValues();
    computeSignatures(signatures);
    updateSimValues(signatures,result);
  }
}
