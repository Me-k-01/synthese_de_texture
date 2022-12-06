#include "permuteur.h"
#include <vector>
#include <random>

Permuteur::Permuteur(int amax):max(amax),i_perm(0) { // Je sais pas ce qu'il manque sur cette ligne que Timothée a fait, donc je commente en attendant
    perm = new int[max]; // Permutation courante
    indices = new int[max]; // Indices possibles

    for(int i=0; i<max; i++){
        indices[i] = i;
        perm[i] = i;
    } 

    generePerm(); // Première permutation
}

Permuteur::~Permuteur() {}

void Permuteur::generePerm() { 
    for (int indMax = max-1; indMax > 0; indMax --) { 
        // Trouve un indice random parmi la partie du tableau avec des indices encore disponnibles
        int indRdm = rand()%indMax; 
        // On permute l'item d'emplacement indMax du tableau avec l'item choisit aléatoirement
        // L'indice dans le tableau choisit aléatoirement ne sera donc plus disponnible pour les prochaines itérations
        int temp = perm[indRdm];
        perm[indRdm] = perm[indMax];
        perm[indMax] = temp;
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