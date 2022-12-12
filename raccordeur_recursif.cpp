
#include "raccordeur_recursif.h"
#include <cstring>
#include <limits>
#include <iostream>


int RaccordeurRecursif::calculerRaccord(MatInt2* distances, int * coupeOut) {
    hauteur = distances->nLignes();
    largeur = distances->nColonnes();  
    this->distances = distances;

    ////////////// Initialisation des tableaux de mémoire des calculs //////////////
    tab_cout = new int [largeur * hauteur];
    tab_coupe = new int*[largeur * hauteur];
    for (int i=0 ; i < largeur * hauteur ; i++) {
        tab_cout[i] = -1;
        tab_coupe[i] = new int[hauteur];
    }
     
    ////////////// Récupération de la coupe optimal //////////////
    int cout_min = std::numeric_limits<int>::max();
    // On test la coupe optimal a partir de chacun des pixels de la permiere ligne
    for (int x = 0; x < largeur; x++) {    
        int coupe_curr[hauteur];
        const int cout_curr = recuSansCalcRedondant(coupe_curr, x, hauteur-1);
        // Si le nouveau coup est plus petit, on le garde
        if (cout_curr < cout_min) {
            cout_min = cout_curr;
            // Et on copie le nouveau chemin minimal dans coupeOut
            memcpy(coupeOut, coupe_curr, sizeof(int) * hauteur); 
        }
    } 

    // Libération de l'espace mémoire alloué au tableau
    delete [] tab_cout ;
    delete [] tab_coupe ;

    return cout_min;
} 


/// calculerRaccordRecu de Thimotée
/*
int RaccordeurRecursif::calculerRaccordRecu(int * const coupe, const int x, const int y) { 
    const int mem_index = x + y*largeur;

    if (tab_cout[mem_index] == -1) {
        if (y == 0) {
            tab_cout[mem_index] = distances->get(x,y);
            tab_coupe[mem_index][y] = x;
        } else {
            int cout_min=std::numeric_limits<int>::max();
            tab_coupe[mem_index][y] = x;
                    
            for(int x_displacement = -1 ; x_displacement<=1 ; x_displacement++) {

                int x_suiv= x + x_displacement;
            
                if (x_suiv < 0 || x_suiv >= largeur) continue;
                
                int cout_suiv = calculerRaccordRecu(coupe, x_suiv, y-1);

                if(cout_suiv <= cout_min){
                    tab_cout[mem_index] = distances->get(x,y)+cout_suiv;

                    for(int i = y-1 ; i>=0;i--) {
                        tab_coupe[mem_index][i] = coupe[i];
                    }
                }
            }
        }
    }
    for(int i=y ; i>=0 ; i--) {
        coupe[i] = tab_coupe[mem_index][i];
    }
    return tab_cout[mem_index];
}
*/
 
int RaccordeurRecursif::recuSansCalcRedondant(int * const coupe, const int x, const int y) {  
    const int mem_index = x + y * largeur;
    // Si la coupe à déjà été calculé une fois, on retourne celle-ci
    if (tab_cout[mem_index] != -1) { 
        memcpy(coupe, tab_coupe[mem_index], hauteur * sizeof(int));
        return tab_cout[mem_index];
    }

    // On ajoute le coût de l'endroit x, y à la coupe actuel 
    int cout_curr = distances->get(y, x); 
    coupe[y] = cout_curr;  
    ////////////// Cas de base //////////////
    if (y == 0) { 
        // On arrête l'exploration de la branche et on retourne le dernier coût
        // Sans oublier d'enregistrer le bout du chemin dans la mémoire
        tab_cout[mem_index] = cout_curr;
        tab_coupe[mem_index][y] = cout_curr; 
        return cout_curr;
    }

    // Sinon on continue l'exploration
    int coupe_min[hauteur];      
    int cout_min = std::numeric_limits<int>::max();

    ////////////// Calcul de la coupe optimale du dessus //////////////
    // Pour chacun des 3 Branchements possibles
    for (int displacement_x = -1; displacement_x <= 1; displacement_x++) { 
        const int next_x = x + displacement_x; // x du voisin du dessus

        // Si x est hors de la matrice, on évite cette branche qui est en dehors de la bande.
        if (next_x < 0 || next_x >= largeur) continue;

        ////////////// Recherche du chemin minimal à partir de cette branche //////////////
        int coupe_test[hauteur];  
        // On lance la recu sur la nouvelle branche et on recupère le coût total minimal
        const int cout = recuSansCalcRedondant(coupe_test, next_x, y-1);
         
        // Et on décide si l'on doit garder la branche
        // La somme des erreurs doit être plus petite que celle de la précédente coupe
        if (cout_min > cout) { 
            // On ne garde que le cout minimal et sa coupe
            memcpy(coupe_min, coupe_test, hauteur * sizeof(int));
            cout_min = cout;
        }
    }

    ////////////// Fin //////////////
    // À la fin, on enregistre la coupe minimal à partir du point x, y 
    memcpy(coupe, coupe_min, y * sizeof(int)); 
    // Et on le mémorise la coupe du chemin optimal trouvé et son coût total 
    tab_cout[mem_index] = cout_curr + cout_min; 
    memcpy(tab_coupe[mem_index], coupe, hauteur * sizeof(int));
    // On retourne le cout du chemin depuis la branche optimal
    return tab_cout[mem_index];
}

RaccordeurRecursif::~RaccordeurRecursif() {
  // pas de ressources a libérer
}

