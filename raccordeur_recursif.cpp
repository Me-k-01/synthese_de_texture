
#include "raccordeur_recursif.h"
#include <cstring>
#include <limits>
#include <iostream>


int RaccordeurRecursif::calculerRaccord(MatInt2* distances, int * coupeOut) {
    hauteur = distances->nLignes();
    largeur = distances->nColonnes();
    this->distances = distances;
    tab_cout = new int [largeur*hauteur];
    tab_coupe = new int*[largeur*hauteur];

    for(int i=0 ; i< largeur*hauteur ; i++) {
        tab_cout[i] = -1;
        tab_coupe[i] = new int[hauteur];
    }
     

    int coutMin = std::numeric_limits<int>::max();
    for (int i = 0; i < largeur; i++) { //largeur    
        int coupeCurr[hauteur];
        const int cout = recuSansCalcRedondant(coupeCurr, i, hauteur-1);
        // Si le nouveau coup est plus petit, on le garde
        if (cout < coutMin) {
            coutMin = cout;
            // et on copy le nouveau chemin minimal sur le pointeur coupeOut
            memcpy(coupeOut, coupeCurr, sizeof(int) * hauteur); 
        }
    } 


    delete [] tab_cout ;
    delete [] tab_coupe ;
    return coutMin;
} 


///a tester 
int RaccordeurRecursif::calculerRaccordRecu(int * coupe, const int x, const int y) { 
    int mem_index = x + y*largeur;

    if (tab_cout[mem_index] == -1) {
        if (y==0) {
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
    for(int i=y ; i>=0;i--) {
        coupe[i]=tab_coupe[mem_index][i];
    }
    return tab_cout[mem_index];
}

// En cours de création
int RaccordeurRecursif::recuSansCalcRedondant(int * coupe, const int x, const int y) { 
    // Si la coupe à déjà été calculé une fois, on la reutilise
    int mem_index = x + y*largeur;
    if (tab_cout[mem_index] != -1) {  
        memcpy( coupe, tab_coupe[mem_index], hauteur * sizeof(int));
        return tab_cout[mem_index];
    }

    // On ajoute le coût de l'endroit x, y à la coupe actuel 
    int coutCurr = distances->get(y, x); 
    coupe[y] = coutCurr;  
    // Cas de base
    if (y == 0) { 
        // On update les tableaux et arrête l'exploration et on retourne le dernier coût
        tab_cout[mem_index] = coutCurr;
        tab_coupe[mem_index][y] = coutCurr; 

        return coutCurr;
    }

    // Sinon on continue l'exploration
    int coupeMin[hauteur];      
    int coutMin = std::numeric_limits<int>::max();

    // Pour chacun des 3 Branchements possibles
    for (int displacementX = -1; displacementX <= 1; displacementX++) { 
        const int currX = x + displacementX;

        // Si x est hors de la matrice, on évite cette branche qui est en dehors de la bande.
        if (currX < 0 || currX >= largeur) continue;

        // Recherche du chemin minimal à partir de cette branche
        int coupeTest[hauteur];  
        // On lance la recu sur la nouvelle branche et on recupère le coût total minimal
        const int cout = recuSansCalcRedondant(coupeTest, currX, y-1);
         
        // Et on décide si l'on doit garder la branche
        // La somme des erreurs doit être plus petite que celle de la précédente coupe
        if (coutMin > cout) { 
            // On ne garde que le cout minimal et sa coupe
            memcpy( coupeMin, coupeTest, hauteur * sizeof(int));
            coutMin = cout;
        }
    }

    // À la fin, on enregistre le cout et la coupe du chemin optimal trouvé à partir du point x, y  
    memcpy( coupe, coupeMin, y * sizeof(int)); 
    tab_cout[mem_index] = coutMin; 
    memcpy( tab_coupe[mem_index], coupe, y * sizeof(int));
    // On retourne le cout du chemin depuis la branche optimal
    return coutCurr + coutMin;
}

RaccordeurRecursif::~RaccordeurRecursif() {
  // pas de ressources a libérer
}

