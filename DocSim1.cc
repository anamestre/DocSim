#include <iostream>
#include <algorithm>
#include "parser.h"

using namespace std;

set<int> reunion (const set<int>& a, const set<int>& b) {
	set<int> result = a;
	for (set<int>::iterator it=b.begin(); it!=b.end(); ++it) {
        result.insert(*it);
    }
    return result;
}

double jaccard(string pathdoc1, string pathdoc2, int k) {
	set<int> a = parser(pathdoc1, k);
	set<int> b = parser(pathdoc2, k);
	set<int> reunionset = reunion(a, b);
	set<int> intersectionset;
	set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(intersectionset, intersectionset.begin()));
	return double(intersectionset.size())/double(reunionset.size());
	
}

int main() {
	string path1, path2;
	int k;
	cout << "Path 1: ";
	cin >> path1;
	cout << "Path 2: ";
	cin >> path2;
	cout << "Shingle size: ";
	cin >> k;
	double jaccardsim = jaccard(path1, path2, k);
	cout << endl << "Jaccard similarity: " << jaccardsim << endl;
}
