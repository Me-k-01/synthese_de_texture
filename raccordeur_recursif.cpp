
#include "raccordeur_recursif.h"
#include <cstring>
#include <limits>

int RaccordeurRecursifNaif::calculerRaccord(MatInt2* distances, int * coupeOut) {
    int hauteur = distances->nLignes();
    int largeur = distances->nColonnes();
    int * coupeCurr = new int[hauteur];
    //std::cout << "recherche i=" << hauteur-1;
    fprintf(stderr, "recherche i=" + hauteur-1);

    int coutMin = calculerRaccordRecu(distances, coupeOut, hauteur-1, 0); 
    
    for (int i = 1; i < largeur; i++){      
        int cout = calculerRaccordRecu(distances, coupeCurr, hauteur-1, i );
        // Si le nouveau coup est plus petit, on le garde
        if (cout < coutMin) {
            coutMin = cout;
            // et on copy le nouveau chemin minimal 
            memcpy(coupeOut, coupeCurr, sizeof(int) * hauteur);
            //for(int j = 0; j < largeur; j++) {
            //    coupe_min[j] = coupe[j];
            //}
        }
    }
    

    //delete[] coupeCurr;
    //fprintf(stderr, "" + coupeOut[0]);
    return coutMin;
}


int RaccordeurRecursifNaif::calculerRaccordRecu(MatInt2* distances, int * coupe, int i, int j) {
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
        coutA = calculerRaccordRecu(distances, coupeA, i-1, j-1);
    else 
        coutA = std::numeric_limits<int>::infinity();
    coutB = calculerRaccordRecu(distances, coupeB, i-1, j);
    if (j < hauteur-1)
        coutC = calculerRaccordRecu(distances, coupeC, i-1, j+1);
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

RaccordeurRecursifNaif::~RaccordeurRecursifNaif() {
  // pas de ressources a libérer
}
