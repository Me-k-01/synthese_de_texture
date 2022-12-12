
#include "raccordeur_iteratif.h"
#include <cstring>
#include <limits>
#include <iostream>


int RaccordeurIteratif::calculerRaccord(MatInt2* distances, int * coupeOut) {
    hauteur = distances->nLignes();
    largeur = distances->nColonnes(); 
    tab_cout = new int [largeur * hauteur];
    tab_coupe = new int*[largeur * hauteur];

    for(int i=0 ; i < largeur * hauteur ; i++) {
        tab_cout[i] = -1;
        tab_coupe[i] = new int[hauteur];
    } 

    int cout_min = std::numeric_limits<int>::max();
    for (int i = 0; i < largeur; i++) { //largeur    
        int coupe_curr[hauteur];
        int cout_curr;
        
        // TODO: Implémenter la solution itérative
        /*
            ajouter du code ici qui modifie cout_curr et coupe_curr
        */


        // Si le nouveau coup est plus petit, on le garde
        if (cout_curr < cout_min) {
            cout_min = cout_curr;
            // Et on copy le nouveau chemin minimal dans coupeOut
            memcpy(coupeOut, coupe_curr, sizeof(int) * hauteur); 
        }
    } 

    delete [] tab_cout ;
    delete [] tab_coupe ;
    return cout_min;
}  
 
RaccordeurIteratif::~RaccordeurIteratif() {
  // pas de ressources a libérer
}

