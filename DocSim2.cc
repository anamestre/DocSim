#include "JaccApprox.hh"
using namespace std;

int main() {
  string file1 = "En el caso de que su baja se prolongase hasta 2017, el alemán no estará en Mestalla contra el Valencia, encuentro de Liga tras la disputa del Mundial de Clubes, que finaliza el 18 de diciembre.";
  string file2 = "alemán adio José Alvalade (5ª jornada de la fase de grupos de la Champions), Spotural Leonesa (vuelta de la Copa del Rey), El Clásico ante el Barcelona en el Camp Nou, Borussia Dortmund en el Santiago Bernabéu (6ª y última jornada de la fase de grupos de la Champions) y Deportivo de la Coruña.En el caso de que su baja se prolongase hasta 2017, el alemán no estará en Mestalla contra el Valencia, encuentro de Liga tras la disputa del Mundial de Clubes, que finaliza el 18 de diciembre.";
  unsigned int k = 4;
  unsigned int t = 50;
  JaccApprox mJA(k,t,file1,file2);
  cout << "Jaccard's approximation of these files is " << mJA.obtainJaccardApproximation() << endl;
}
