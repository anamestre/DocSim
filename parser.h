//
// Created by gorka on 05/11/16.
//

#ifndef DOCSIM_PARSER_H
#define DOCSIM_PARSER_H

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

//Pre: c es un caracter
//Post: retorna cert si c és un espai, un salt de línia o un tabulador
bool is_whitespace (char c) {
    return c == ' ' or c == '\n' or c == '\t';
}

int hash_shingle(string shingle) {
	int maxhash = 0x11111111;
	int hash = 0;
	for (int i = 0; i < shingle.size(); ++i) {
		hash += shingle[i];
	}
	return hash%maxhash;
}


//Pre: path indica el camí a un document de text, k es mes gran que zero
//Post: retorna un conjunt amb tots els k-shingles extrets del document
set<int> parser(string path, int k) {
    ifstream file;
    file.open(path.c_str());
    if (file.is_open()) {
        char c = 'a';   //"Falsa" inicialitzacio
        int i, j;
        i = j = 0;
        set<int> shingles;
        while (c != EOF) {
            string s;
            bool whitespace = false;
            file.seekg(i);
            while (j < k and c != EOF) {
                c = file.get();
                if (is_whitespace(c) and c != EOF) {
                    if (not whitespace) {   //Permet tractar el primer whitespace i ignorar la resta
                        s += ' ';       //Transformem tots els tipus de whitespace en un espai per millor visualitzacio
                        //s += '_';     //Per debug: permet veure millor els espais
                        ++j;
                        whitespace = true;
                    }
                }
                else if (c != EOF) {
                    whitespace = false;
                    c = tolower(c);
                    s += c;
                    ++j;
                }
            }
            if (s.size() == k) shingles.insert(hash_shingle(s));
            j = 0;
            ++i;
        }
        file.close();
        return shingles;

    }
    else cout << "Error: l'arxiu no s'ha pogut llegir." << endl;
}

#endif //DOCSIM_PARSER_H
