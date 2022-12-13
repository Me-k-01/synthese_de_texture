
#include "raccordeur_iteratif.h"
#include <cstring>
#include <limits>
 
int RaccordeurIteratif::calculerRaccord(MatInt2* distances, int * coupeOut) {
    const int hauteur = distances->nLignes();
    const int largeur = distances->nColonnes(); 
    // Pour l'optimisation de mémoire:
    // On pourra avoir un tableau[largeur] qui change à chaque étape y.
    int tabCout[largeur]; 
    // Ainsi qu'un tableau[largeur][hauteur] qui évolue au fils des lignes.
    int tabCoupe[largeur][hauteur];  

    ////////////// Initialisation des tableaux de mémoire des calculs //////////////
    for (int x=0 ; x < largeur ; x++) {
        tabCout[x] = distances->get(0, x); 
        tabCoupe[x][0] = x; //tabCout[x];
    } 

    ////////////// Calcul de toutes les coupes ////////////// 
    for (int y = 1; y < hauteur; y++)   {  
        int newTabCout[largeur]; // Nouvelle ligne de cout total 
        int newTabCoupe[largeur][hauteur];

        for (int x = 0; x < largeur; x++) {  
            int coutMin = std::numeric_limits<int>::max(); 
            int couMinX; 

            // Selection du chemin le moins couteux
            // Pour cela on inspecte les 3 voisins de la ligne précédente
            for (int displacementX = -1; displacementX <= 1; displacementX++) { 
                const int voisinX = x + displacementX; // x du voisin du dessus 
                // Si x est hors de la matrice, on évite cette branche qui est en dehors de la bande.
                if (voisinX < 0 || voisinX >= largeur) continue; 

                // On choisit le meilleur coût total parmi les 3 voisins
                if (tabCout[voisinX] < coutMin) {
                    coutMin = tabCout[voisinX];
                    couMinX = voisinX;
                }
            }
 
            // On update le tableau de la meilleur coupe  
            memcpy(newTabCoupe[x], tabCoupe[couMinX], y * sizeof(int)); // On recopie de 0 à y-1
            newTabCoupe[x][y] = x; // On edit la ligne courante
            // Et le cout total 
            newTabCout[x] = coutMin + distances->get(y, x);  
        }
        // On remplace la ligne courante avec la nouvelle ligne qui vient d'être calculée
        memcpy(tabCout, newTabCout, largeur * sizeof(int)); 
        memcpy(tabCoupe, newTabCoupe, largeur * hauteur * sizeof(int)); // On remplace
    }  
    ////////////// Selection de la coupe optimal ////////////// 
    // La coupe optimal est celle qui possède le coût total le plus bas
    int indMin = getMinIndex(tabCout, largeur); 
    // On copie le chemin minimal dans coupeOut
    memcpy(coupeOut, tabCoupe[indMin], hauteur * sizeof(int));  
    int coutMin = tabCout[indMin];
    
    return coutMin;
}   

// Trouve l'indice du minimum d'un tableau
int RaccordeurIteratif::getMinIndex(const int * const array, const int size) {  
    int ind_min = 0; 
    for (int i = 1; i < size; i++) { 
        if (array[ind_min] > array[i]) { 
            ind_min = i; 
        }
    } 
    return ind_min;
}
RaccordeurIteratif::~RaccordeurIteratif() {
  // pas de ressources a libérer
}

