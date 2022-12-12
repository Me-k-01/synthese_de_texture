
#include "raccordeur_iteratif.h"
#include <cstring>
#include <limits>
#include <iostream>


int RaccordeurIteratif::calculerRaccord(MatInt2* distances, int * coupeOut) {
    const int hauteur = distances->nLignes();
    const int largeur = distances->nColonnes(); 
    // Pour l'opti de mémoire, on pourra conserver un tableau[largeur] qui change à chaque étape y.
    int tab_cout [largeur]; 
    int tab_coupe [largeur][hauteur];  

    ////////////// Initialisation des tableaux de mémoire des calculs //////////////
    for (int x=0 ; x < largeur ; x++) {
        tab_cout[x] = distances->get(0, x); 
        tab_coupe[x][0] = tab_cout[x];
    } 

    ////////////// Calcul de toutes les coupes ////////////// 
    for (int y = 1; y < hauteur; y++)   {   
        for (int x = 0; x < largeur; x++) {  
            int cout_min = std::numeric_limits<int>::max(); 
            int new_tab_cout[largeur]; // Nouvelle ligne de cout total

            // On inspecte les 3 voisins de la ligne précédente
            for (int displacement_x = -1; displacement_x <= 1; displacement_x++) { 
                const int prev_x = x + displacement_x; // x du voisin du dessus 
                // Si x est hors de la matrice, on évite cette branche qui est en dehors de la bande.
                if (prev_x < 0 || prev_x >= largeur) continue; 

                // On choisit le meilleur coût total parmi ceux de la ligne précédente
                if (cout_min > tab_cout[prev_x] ) { 
                    new_tab_cout[x] = tab_cout[prev_x] + distances->get(y, x);  
                    // On update le tableau de la meilleur coupe
                    memcpy(tab_coupe[x], tab_coupe[prev_x], y * sizeof(int)); // On recopie de 0 a y-1
                    cout_min = tab_cout[prev_x];
                }
            }
            tab_coupe[x][y] = distances->get(y, x); 
            // On remplace la ligne courante avec la nouvelle ligne qui vient d'être calculée
            memcpy(tab_cout, new_tab_cout, largeur * sizeof(int)); 
        }
 
    } 

    ////////////// Selection de la coupe optimal ////////////// 
    // La coupe optimal est celle qui possède le coût total le plus bas
    int ind_min = getMinIndex(tab_cout, largeur); 
    // On copie le chemin minimal dans coupeOut
    memcpy(coupeOut, tab_coupe[ind_min], hauteur * sizeof(int));  
    int cout_min = tab_cout[ind_min];
    
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

