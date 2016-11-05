//
// Created by gorka on 05/11/16.
//

#include <set>
#include <string>
#include <iostream>
#include "parser.h"
using namespace std;

//Pre: s es un set
//Post: imprimeix per pantalla el contingut del set
void print_set(const set<string>& s) {
    cout << "CONTINGUT DEL SET" << endl;
    for (set<string>::iterator it=s.begin(); it!=s.end(); ++it) {
        cout << *it << endl;
    }
}

int main() {
    cout << "Test" << endl;
    cout << "Introdueix el camí de l'arxiu a llegir:" << endl;
    string path;
    cin >> path;
    cout << "Introdueix la longitud dels shingles:" << endl;
    int k;
    cin >> k;
    set<string> shingles = parser(path, k);
    print_set(shingles);
}