
#include "raccordeur_recursif.h"
#include <cstring>

int RaccordeurRecursifNaif::calculerRaccord(MatInt2* distances, int *coupe) {
    int hauteur = distances->nLignes();
    int largeur = distances->nColonnes();
    int cout;
    int * coupe_min = new int[hauteur];
    int min = calculerRaccordRecu(distances, coupe_min,hauteur-1,0); ;
  
  
    for ( int i = 1; i < largeur; i++){      
        cout = calculerRaccordRecu(distances, coupe, hauteur-1, i );
        if(cout < min) {
            min = cout;

            for(int j = 0; j < largeur; j++) {
                
                coupe_min[j] = coupe[j];
                
            }
        }
    }
  
    for(int j = 0; j < nLignes; j++){
        coupe[j] = coupe_min[j];      
    }
    delete[] coupe_min;
    return min;
}



int RaccordeurRecursifNaif::calculerRaccordRecu(MatInt2* distances, int * coupe, int i, int j) {
    int hauteur = distances->nLignes();
    int s = sizeof(int) * hauteur;

    // Cas de base
    if (i < 0) { 
        // Calcul du coup final
        int coup = 0;
        for (int x = 0; x < hauteur; x++) {
            coup += coupe[x];
        }
        return coup;
    }
    // 3 Branchement possible
    int * coupeA = memcpy( &coupeA, &coupe, s);
    int * coupeB = memcpy( &coupeB, &coupe, s);
    int * coupeC = memcpy( &coupeC, &coupe, s);

    coupe[i] = distances->get(i, j);
    coupe[i] = distances->get(i, j);
    coupe[i] = distances->get(i, j);

    int coutA = calculerRaccordRecu(distances, coupeA, i-1, j-1);
    int coutB = calculerRaccordRecu(distances, coupeB, i-1, j);
    int coutC = calculerRaccordRecu(distances, coupeC, i-1, j+1);

    // Selection de la branche plus petit et edition de la coupe minimale
    if (coutA < coutB && coutA < coutC) { // coutA plus petit 
        coupe = memcpy( &coupe, &coupeA, s);
        delete[] coupeB;
        delete[] coupeC;
        return coutA;
    }
    if (coutB < coutA && coutB < coutC) { // coutB plus petit
        coupe = memcpy( &coupe, &coupeB, s);
        delete[] coupeA;
        delete[] coupeC;
        return coutB;
    }
    if (coutC < coutA && coutC < coutB) { // coutC plus petit
        coupe = memcpy( &coupe, &coupeC, s);
        delete[] coupeA;
        delete[] coupeB;
        return coutC;
    }
}

RaccordeurRecursifNaif::~RaccordeurRecursifNaif() {
  // pas de ressources a liberer
}
