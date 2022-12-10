
#include "raccordeur_recursif_naif.h"
#include <cstring>
#include <limits>
#include <iostream>

int RaccordeurRecursifNaif::calculerRaccord(MatInt2* distances, int * coupeOut) {
    const int hauteur = distances->nLignes();
    const int largeur = distances->nColonnes();
    
    int coutMin = std::numeric_limits<int>::max();
    for (int i = 0; i < largeur; i++) { //largeur    
        int coupeCurr[hauteur];
        const int cout = calculerRaccordRecu(distances, coupeCurr, largeur, hauteur, i, hauteur-1);
        // Si le nouveau coup est plus petit, on le garde
        if (cout < coutMin) {
            coutMin = cout;
            // et on copy le nouveau chemin minimal sur le pointeur coupeOut
            memcpy(coupeOut, coupeCurr, sizeof(int) * hauteur);
            /*
            for (int j = 0; j < hauteur; j++) {
                coupeOut[j] = coupeCurr[j];
            }
            */
        }
    } 
  
    return coutMin;
} 
int RaccordeurRecursifNaif::calculerRaccordRecu(MatInt2 * const distances, int * coupe, const int largeur, const int hauteur, const int x, const int y) { 
    // On ajoute le coût de l'endroit x, y à la coupe actuel 
    int coutCurr = distances->get(y, x); 
    coupe[y] = coutCurr; 
    // Cas de base
    if (y == 0) { 
        // On arrête l'exploration et on retourne le dernier coût
        return coutCurr;
    }

    // Sinon on continue l'exploration
    int coupeMin[hauteur];      
    int coutMin = std::numeric_limits<int>::max();

    // Pour chacun des 3 Branchements possibles
    for (int displacement = -1; displacement <= 1; displacement++) { 
        const int currX = x + displacement;

        // Si x est hors de la matrice, on évite cette branche qui est en dehors de la bande.
        if (currX < 0 || currX >= largeur) continue;

        // Recherche du chemin minimal à partir de cette branche
        int coupeTest[hauteur];  
        const int cout = calculerRaccordRecu(distances, coupeTest, largeur, hauteur, currX, y-1);
         
        
        // Et on décide si l'on doit garder la branche
        // La somme des erreurs doit être plus petite que celle de la précédente coupe
        if (coutMin > cout) { 
            // On update donc la coupe minimal et le cout
            memcpy( coupeMin, coupeTest, hauteur * sizeof(int));
            //for (int i = 0; i < hauteur; i++) { coupeMin[i] = coupeTest[i];}
            coutMin = cout;
        }
    }

    // On update la coupe avec le nouveau morceau de chemin optimal qui a été trouvé 
    memcpy( coupe, coupeMin, y * sizeof(int));
    //for (int i = 0; i < hauteur; i++) { coupe[i] = coupeMin[i];}
    // On retourne le cout du chemin depuis la branche optimal
    return coutCurr + coutMin;
}


RaccordeurRecursifNaif::~RaccordeurRecursifNaif() {
  // pas de ressources a libérer
}
