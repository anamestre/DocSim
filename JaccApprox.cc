#include "JaccApprox.hh"
using namespace std;

JaccApprox::JaccApprox(unsigned int k_, unsigned int t_, string mFile_1_, string mFile_2_) {
  k = k_;
  t = t_;
  mFile_1 = mFile_1_;
  mFile_2 = mFile_2_;
  JaccApprox::bigPrimesVector = {547,563,733,619,691,829,911,701,599,601,827,659};
}

bool JaccApprox::sameMinhashSignature() {
  return minhashSignature(mFile_1) == minhashSignature(mFile_2);
}

unsigned int JaccApprox::hashFromShingle(const string& shingle) {
  unsigned int a, b;
  a = mHV.hash_1;
  b = mHV.hash_2;
  for (int i = 0; i < shingle.length(); ++i) {
    a = (a*b) + shingle[i];
  }
  return a%(0x11111111);
}

unsigned int JaccApprox::minhashSignature(const string& mFile) {
  if (mFile.length() < k) return hashFromShingle(mFile);
  unsigned int minimumHash = hashFromShingle(mFile.substr(0,k));
  for (int i = 1; i <= mFile.length() - k; ++i) {
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

double JaccApprox::obtainJaccardApproximation() {
  unsigned int signature_matches = 0;
  for (unsigned int i = 0; i < t; ++i) {
    getNewHashValues();
    if (sameMinhashSignature()) signature_matches += 1;
  }
  return ((double)signature_matches/(double) t);
}
