#include "permuteur.h"
#include <vector>
Permuteur::Permuteur(int max):i_perm(0),this->max(max){
   
   perm = new int[max]; // permutation courante
   indices = new int[max]; // Indices possibles
   
   for(int i=0;i<max;i++){
        indices[i]=i;
      

   } 

}

Permuteur::~Permuteur(){

}


void Permuteur::generateFlo() {
    int ind = max;
    Vector<int> possibleIndices ;
    for (int i = 0; i<max; i++) {
        int indRdm = random()%possibleIndices.size();
        perm[i] = possibleIndices[indRdm];
        possibleIndices.remove(ind)
    }
    
}


void Permuteur::generePermRom() {
    int deja_present[max];
    for(int i=0;i<max;i++){
        int n = random() % (max);
        while(std::count(begin(deja_present), end(deja_present), n)!=0){
            n=random() % (max);
        }
        perm[i]=n;
        deja_present[i]=n;
    }
}

int Permuteur::suivant(){
    i_perm ++;

    if (i_perm == max) {
        // Génerer un nouveau tableau de permutation
        generePerm();
        i_perm = 0;
    }
    
    return perm[i_perm];
}