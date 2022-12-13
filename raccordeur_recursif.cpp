
#include "raccordeur_recursif.h"
#include <cstring>
#include <limits> 


int RaccordeurRecursif::calculerRaccord(MatInt2* distances, int * coupeOut) {
    hauteur = distances->nLignes();
    largeur = distances->nColonnes();  
    this->distances = distances;

    ////////////// Initialisation des tableaux de mémoire des calculs //////////////
    tabCout = new int [largeur * hauteur];
    tabCoupe = new int*[largeur * hauteur];
    for (int i=0 ; i < largeur * hauteur ; i++) {
        tabCout[i] = -1;
        tabCoupe[i] = new int[hauteur];
    }
     
    ////////////// Récupération de la coupe optimal //////////////
    int coutMin = std::numeric_limits<int>::max();
    // On test la coupe optimal a partir de chacun des pixels de la permiere ligne
    for (int x = 0; x < largeur; x++) {    
        int coupe_curr[hauteur];
        const int coutCurr = recuSansCalcRedondant(coupe_curr, x, hauteur-1);
        // Si le nouveau coup est plus petit, on le garde
        if (coutCurr < coutMin) {
            coutMin = coutCurr;
            // Et on copie le nouveau chemin minimal dans coupeOut
            memcpy(coupeOut, coupe_curr, sizeof(int) * hauteur); 
        }
    } 

    // Libération de l'espace mémoire alloué au tableau
    delete [] tabCout ;
    delete [] tabCoupe ;

    return coutMin;
} 


/// calculerRaccordRecu de Timotée
/*
int RaccordeurRecursif::calculerRaccordRecu(int * const coupe, const int x, const int y) { 
    const int memIndex = x + y*largeur;

    if (tabCout[memIndex] == -1) {
        if (y == 0) {
            tabCout[memIndex] = distances->get(x,y);
            tabCoupe[memIndex][y] = x;
        } else {
            int coutMin=std::numeric_limits<int>::max();
            tabCoupe[memIndex][y] = x;
                    
            for(int x_displacement = -1 ; x_displacement<=1 ; x_displacement++) {

                int x_suiv= x + x_displacement;
            
                if (x_suiv < 0 || x_suiv >= largeur) continue;
                
                int cout_suiv = calculerRaccordRecu(coupe, x_suiv, y-1);

                if(cout_suiv <= coutMin){
                    tabCout[memIndex] = distances->get(x,y)+cout_suiv;

                    for(int i = y-1 ; i>=0;i--) {
                        tabCoupe[memIndex][i] = coupe[i];
                    }
                }
            }
        }
    }
    for(int i=y ; i>=0 ; i--) {
        coupe[i] = tabCoupe[memIndex][i];
    }
    return tabCout[memIndex];
}
*/
 
int RaccordeurRecursif::recuSansCalcRedondant(int * const coupe, const int x, const int y) {  
    const int memIndex = x + y * largeur;
    // Si la coupe à déjà été calculé une fois, on retourne celle-ci
    if (tabCout[memIndex] != -1) { 
        memcpy(coupe, tabCoupe[memIndex], hauteur * sizeof(int));
        return tabCout[memIndex];
    }

    // On ajoute le x dans la coupe 
    int coutCurr = distances->get(y, x); 
    coupe[y] = x;  
    ////////////// Cas de base //////////////
    if (y == 0) { 
        // On arrête l'exploration de la branche et on retourne le dernier coût
        // Sans oublier d'enregistrer le bout du chemin dans la mémoire
        tabCout[memIndex] = coutCurr;
        tabCoupe[memIndex][y] = x; 
        return coutCurr;
    }

    // Sinon on continue l'exploration
    int coupeMin[hauteur];      
    int coutMin = std::numeric_limits<int>::max();

    ////////////// Calcul de la coupe optimale du dessus //////////////
    // Pour chacun des 3 Branchements possibles
    for (int displacementX = -1; displacementX <= 1; displacementX++) { 
        const int nextX = x + displacementX; // x du voisin du dessus

        // Si x est hors de la matrice, on évite cette branche qui est en dehors de la bande.
        if (nextX < 0 || nextX >= largeur) continue;

        ////////////// Recherche du chemin minimal à partir de cette branche //////////////
        int coupeTest[hauteur];  
        // On continue la recu sur la nouvelle branche et on recupère le coût total minimal
        const int cout = recuSansCalcRedondant(coupeTest, nextX, y-1);
         
        // Et on décide si l'on doit garder la branche
        // La somme des erreurs doit être plus petite que celle de la précédente coupe
        if (coutMin > cout) { 
            // On ne garde que le coût minimal et sa coupe
            coutMin = cout;
            memcpy(coupeMin, coupeTest, hauteur * sizeof(int)); 
        }
    }

    ////////////// Fin //////////////
    // À la fin, on enregistre la coupe minimal à partir du point x, y 
    memcpy(coupe, coupeMin, y * sizeof(int)); 
    // Et on le mémorise la coupe du chemin optimal trouvé et son coût total 
    tabCout[memIndex] = coutCurr + coutMin; 
    memcpy(tabCoupe[memIndex], coupe, (y+1) * sizeof(int));
    // On retourne le cout du chemin depuis la branche optimal
    return tabCout[memIndex];
}

RaccordeurRecursif::~RaccordeurRecursif() {
  // pas de ressources a libérer
}

