
#include "raccordeur_iteratif.h"
#include <cstring>
#include <limits>
#include <iostream>


int RaccordeurIteratif::calculerRaccord(MatInt2* distances, int * coupeOut) {
    const int hauteur = distances->nLignes();
    const int largeur = distances->nColonnes(); 
    int * const tab_cout = new int [largeur * hauteur]; // Pour l'opti de mémoire, on pourra conserver un tableau[largeur] qui change à chaque étape y.
    int ** const tab_coupe = new int*[largeur * hauteur];  

    ////////////// Initialisation des tableaux de mémoire des calculs //////////////
    for (int x=0 ; x < largeur ; x++) {
        for (int y = 0; y < hauteur; y++) { 
            const int mem_index = x + y * largeur;
            tab_cout[mem_index] = -1;
            tab_coupe[mem_index] = new int[hauteur];
            tab_coupe[mem_index][0] = distances->get(y, x);
        }
    } 


    ////////////// Calcul de toutes les coupes ////////////// 
    for (int y = 0; y < hauteur; y++)   {  
        
        // TODO: Implémenter la solution itérative
        /*
            ajouter du code ici qui modifie cout_curr et coupe_curr
        */
        for (int x = 0; x < largeur; x++) {
            
        }
 
    } 

    ////////////// Selection de la coupe optimal ////////////// 
    // La coupe optimal est celle qui possède le coût total le plus bas
    int ind_min = getMinIndex(tab_cout, largeur); 
    // On copie le chemin minimal dans coupeOut
    memcpy(coupeOut, tab_coupe[ind_min], sizeof(int) * hauteur);  
    int cout_min = tab_cout[ind_min];

    // Libération de l'espace mémoire alloué au tableau
    delete [] tab_cout ;
    delete [] tab_coupe ;
    
    return cout_min;
}  

// Trouve l'indice du minimum d'un tableau
int RaccordeurIteratif::getMinIndex(const int * const array, const int size) {  
    int ind_min = 0; 
    for (int i = 1; i < size; i++) { 
        if (array[ind_min] < array[i]) { 
            ind_min = i; 
        }
    } 
    return ind_min;
}
RaccordeurIteratif::~RaccordeurIteratif() {
  // pas de ressources a libérer
}

