
#include "LocalitySensitive.hh"
#include <iostream>
using namespace std;


int main(){
  string file1 = "En el caso de que su baja se prolonga other siiiiiise hasta 2017, el alemán no estará en Mestalla contra el Valencia, encuentro de Liga tras la disputa del Mundial de Clubes, que finaliza el 18 de diciembre.";
  string file2 = "alemán adio José Alvalade (5ª jornad other siiiiiia de la fase de grupos de la Champions), Spotural Leonesa (vuelta de la Copa del Rey), El Clásico ante el Barcelona en el Camp Nou, Borussia Dortmund en el Santiago Bernabéu (6ª y última jornada de la fase de grupos de la Champions) y Deportivo de la Coruña.En el caso de que su baja se prolongase hasta 2017, el alemán no estará en Mestalla contra el Valencia, encuentro de Liga tras la disputa del Mundial de Clubes, que finaliza el 18 de diciembre.";
  string file3 = "Heeeeeeeello from the other siiiiiiide";
  string file4 = "parapjsgnsjgfgfdhdfljg other siiiiii";
  int k, t, band, modBuckets;
  cout << "Insereix k, t, nombre de bands i nombre de buckets: " << endl;
  cin >> k >> t >> band >> modBuckets;
  
  vector<string* > files;
  files.push_back(&file1);
  files.push_back(&file2);
  files.push_back(&file3);
  files.push_back(&file4);
  
  LocalitySensitive LSH(files, k, t, band, modBuckets);
  LSH.printCandidates();
}
  