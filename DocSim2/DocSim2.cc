#include "JaccApprox.hh"
using namespace std;

void mostraResultat(const vector<vector< double > >& matriu) {
  for (int i = 0; i < matriu.size(); ++i) {
    for (int j = 0; j < matriu.size(); ++j) {
      if (i == j) cout << "X ";
      else cout << matriu[i][j] << " ";
    }
    cout << endl;
  }
}

void readFiles(vector<string>& mFiles) {
  string file1 = "En el caso de que su baja se prolonga other siiiiiise hasta 2017, el alemán no estará en Mestalla contra el Valencia, encuentro de Liga tras la disputa del Mundial de Clubes, que finaliza el 18 de diciembre.";
  string file2 = "alemán adio José Alvalade (5ª jornad other siiiiiia de la fase de grupos de la Champions), Spotural Leonesa (vuelta de la Copa del Rey), El Clásico ante el Barcelona en el Camp Nou, Borussia Dortmund en el Santiago Bernabéu (6ª y última jornada de la fase de grupos de la Champions) y Deportivo de la Coruña.En el caso de que su baja se prolongase hasta 2017, el alemán no estará en Mestalla contra el Valencia, encuentro de Liga tras la disputa del Mundial de Clubes, que finaliza el 18 de diciembre.";
  string file3 = "Heeeeeeeello from the other siiiiiiide";
  string file4 = "parapjsgnsjgfgfdhdfljg other siiiiii";
  mFiles.push_back(file1);
  mFiles.push_back(file3);
  mFiles.push_back(file2);
  mFiles.push_back(file4);
}
                           //no puede ser const porque escribo su referencia
void getReferencesFromFiles(vector<string>& mFiles, vector<string*>& mFileReferences) {
  for (int i = 0; i < mFiles.size(); ++i)
    mFileReferences.push_back(&mFiles[i]);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cout << "Usage: ./DocSim2.x k t" << endl;
    exit(1);
  }
  unsigned int k = atoi(argv[1]);
  unsigned int t = atoi(argv[2]);
  vector<string> mFiles;
  readFiles(mFiles);
  vector<string*> mFileReferences;
  getReferencesFromFiles(mFiles,mFileReferences);
  JaccApprox mJA(k,t,mFileReferences);
  vector<vector< double > > matriu(mFiles.size(),vector<double>(mFiles.size(),0.0));
  mJA.obtainJaccardApproximation(matriu);
  mostraResultat(matriu);
}
