#include "permuteur.h"
#include <vector>
#include <random>
#include <iostream>

Permuteur::Permuteur(int max) { 
//Permuteur::Permuteur(int max):i_perm(0),this->max(max) { // Je sais pas ce qu'il manque sur cette ligne que Timothé a fait, donc je commente en attendant
    i_perm = 0;
    this->max = max;

    perm = new int[max]; // permutation courante
    indices = new int[max]; // Indices possibles

    for(int i=0; i<max; i++){
        indices[i] = i;
        perm[i] = i;
    } 
    
    generePerm(); // Première permutation
}

Permuteur::~Permuteur() {
}

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

/*
void Permuteur::generateFlo() {
    int ind = max;
    Vector<int> possibleIndices ; // TODO: initialiser
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
*/

int Permuteur::suivant(){
    i_perm ++;

    if (i_perm == max) {
        // Génerer un nouveau tableau de permutation
        generePerm();
        i_perm = 0;
    }
    
    return perm[i_perm];
}