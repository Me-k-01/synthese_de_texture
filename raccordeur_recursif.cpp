
#include "raccordeur_recursif.h"
#include <cstring>
#include <limits>
#include <iostream>

int RaccordeurRecursifNaif::calculerRaccord(MatInt2* distances, int * coupeOut) {
    const int hauteur = distances->nLignes();
    const int largeur = distances->nColonnes();
    //int * coupeCurr = new int[hauteur]; 
    //for (int i = 0; i < hauteur; i++) { coupeOut[i] = 0;}  
                                                                        
    //std::cout << "recherche y=" << hauteur-1 << std::endl;
    
    int coutMin = std::numeric_limits<int>::max();
    for (int i = 0; i < largeur; i++){ //largeur   // Testing de i = 2
        int coupeCurr[hauteur];                        //for (int i = 0; i < hauteur; i++) { coupeCurr[i] = 0;} 
        const int cout = calculerRaccordRecu(distances, coupeCurr, largeur, hauteur, i, hauteur-1 );
        // Si le nouveau coup est plus petit, on le garde
        if (cout < coutMin) {
            coutMin = cout;
            // et on copy le nouveau chemin minimal sur le pointeur coupeOut
            //memcpy(coupeOut, coupeCurr, sizeof(coupeCurr) * hauteur);
            
            for(int j = 0; j < hauteur; j++) {
                coupeOut[j] = coupeCurr[j];
            }
            
        }
    } 

    std::cout << "coupe: ";
    for (int i = 0; i < hauteur; i++) {
        std::cout  << coupeOut[i] << " , " ;
    } 
    std::cout << std::endl << "coutMin = " << coutMin << std::endl;
    return coutMin;
}



int RaccordeurRecursifNaif::calculerRaccordRecu(MatInt2 * const distances, int * coupe, const int largeur, const int hauteur, const int x, const int y) { 
    // On ajoute le coût de l'endroit x, y à la coupe actuel 
    int coutCurr = distances->get(y, x); 
    coupe[y] = coutCurr;
    //std::cout << "y" << y << std::endl;
    if (y == 0) { 
        // On arrête l'exploration et on retourne le dernier coût
        return coutCurr;
    }

    // Sinon on continue l'exploration
    int coupeMin[hauteur];                                                              //for (int i = 0; i < hauteur; i++) { coupeMin[i] = 0;}
    int coutMin = std::numeric_limits<int>::max();

    // Pour chacun des 3 Branchements possibles
    for (int displacement = -1; displacement <= 1; displacement++) { 
        const int currX = x + displacement;

        // Si x est hors de la matrice, on évite cette branche qui est en dehors de la bande.
        if (currX < 0 || currX >= largeur) continue;

        // Recherche du chemin minimal à partir de cette branche
        int coupeTest[hauteur];                                                            //for (int i = 0; i < hauteur; i++) { coupeTest[i] = 0;}
        const int cout = calculerRaccordRecu(distances, coupeTest, largeur, hauteur, currX, y-1);
         
        
        // Et on décide si l'on doit garder la branche
        // La somme des erreurs doit être plus petite que celle de la précédente coupe
        if (coutMin > cout) { 
            // On update donc la coupe minimal et le cout
            memcpy( coupeMin, coupeTest, hauteur * sizeof(coupeTest));
            //for (int i = 0; i < hauteur; i++) { coupeMin[i] = coupeTest[i];}
            coutMin = cout;
        }
    }

    std::cout << "coupeMin pour y = " << y << ":" << std::endl;  
    for (int i = 0; i < hauteur; i++)
    {
        std::cout << coupeMin[i] << " , ";
    }
    std::cout << std::endl;

    // On update la coupe avec le chemin optimal qui a été trouvé 
    //memcpy( coupe, coupeMin, y * sizeof(int));
    for (int i = 0; i < y; i++) { 
         
        coupe[i] = coupeMin[i]; 
    } 
    // On retourne le cout du chemin depuis la branche optimal
    return coutCurr + coutMin;
}
/*
int RaccordeurRecursifNaif::calculerRaccordRecu2(MatInt2* distances, int * coupe, int i, int j) {
    // Coupe correspond à la branche des erreurs
    int hauteur = distances->nLignes();
    // Cas de base
    if (i < 0) { 
        // Calcul du coup final
        int coup = 0;
        for (int x = 0; x < hauteur; x++) {
            coup += coupe[x];
        }
        return coup;
    }
    int s = sizeof(int) * hauteur;
    // 3 Branchement possible
    int * coupeA = new int[hauteur];
    int * coupeB = new int[hauteur];
    int * coupeC = new int[hauteur];
    memcpy( coupeA, coupe, s);
    memcpy( coupeB, coupe, s);
    memcpy( coupeC, coupe, s);
    coupe[i] = distances->get(i, j);
    coupe[i] = distances->get(i, j);
    coupe[i] = distances->get(i, j);

    int coutA; int coutB; int coutC;
    if (j > 0)
        coutA = calculerRaccordRecu2(distances, coupeA, i-1, j-1);
    else 
        coutA = std::numeric_limits<int>::infinity();
    coutB = calculerRaccordRecu2(distances, coupeB, i-1, j);
    if (j < hauteur-1)
        coutC = calculerRaccordRecu2(distances, coupeC, i-1, j+1);
    else 
        coutC = std::numeric_limits<int>::infinity();

    // Selection de la branche plus petit et edition de la coupe minimale
    // coutA plus petit
    if (coutA < coutB && coutA < coutC) { 
        memcpy( coupe, coupeA, s);
        delete[] coupeB;
        delete[] coupeC;
        return coutA;
    }
    // coutB plus petit
    if (coutB < coutA && coutB < coutC) {
        memcpy( coupe, coupeB, s);
        delete[] coupeA;
        delete[] coupeC;
        return coutB;
    }
    // coutC plus petit
    if (coutC < coutA && coutC < coutB) {
        memcpy( coupe, coupeC, s);
        delete[] coupeA;
        delete[] coupeB;
        return coutC;
    }
}
*/
RaccordeurRecursifNaif::~RaccordeurRecursifNaif() {
  // pas de ressources a libérer
}
