
#include "raccordeur_iteratif.h"
#include <cstring>
#include <limits>


int RaccordeurIteratif::calculerRaccord(MatInt2* distances, int * coupeOut) {
    const int hauteur = distances->nLignes();
    const int largeur = distances->nColonnes(); 
    // Pour l'optimisation de mémoire:
    // On pourra avoir un tableau[largeur] qui change à chaque étape y.
    int tab_cout[largeur]; 
    // Ainsi qu'un tableau[largeur][hauteur] qui évolue au fils des lignes.
    int tab_coupe[largeur][hauteur];  

    ////////////// Initialisation des tableaux de mémoire des calculs //////////////
    for (int x=0 ; x < largeur ; x++) {
        tab_cout[x] = distances->get(0, x); 
        tab_coupe[x][0] = tab_cout[x];
    } 

    ////////////// Calcul de toutes les coupes ////////////// 
    for (int y = 1; y < hauteur; y++)   {  
        int new_tab_cout[largeur]; // Nouvelle ligne de cout total 
        int new_tab_coupe[largeur][hauteur];

        for (int x = 0; x < largeur; x++) {  
            int cout_min = std::numeric_limits<int>::max(); 
            int x_cout_min; 

            // Selection du chemin le moins couteux
            // Pour cela on inspecte les 3 voisins de la ligne précédente
            for (int displacement_x = -1; displacement_x <= 1; displacement_x++) { 
                const int x_voisin = x + displacement_x; // x du voisin du dessus 
                // Si x est hors de la matrice, on évite cette branche qui est en dehors de la bande.
                if (x_voisin < 0 || x_voisin >= largeur) continue; 

                // On choisit le meilleur coût total parmi les 3 voisins
                if (tab_cout[x_voisin] < cout_min) {
                    cout_min = tab_cout[x_voisin];
                    x_cout_min = x_voisin;
                }
            }
 
            // On update le tableau de la meilleur coupe 
            memcpy(new_tab_coupe[x], tab_coupe[x_cout_min], y * sizeof(int)); // On recopie de 0 à y-1
            new_tab_coupe[x][y] = distances->get(y, x); 
            // Et le cout total 
            new_tab_cout[x] = cout_min + distances->get(y, x);  
        }
        // On remplace la ligne courante avec la nouvelle ligne qui vient d'être calculée
        memcpy(tab_cout, new_tab_cout, largeur * sizeof(int)); 
        memcpy(tab_coupe, new_tab_coupe, largeur * hauteur * sizeof(int)); 
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

