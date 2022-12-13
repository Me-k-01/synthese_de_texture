#include <iostream>
#include "matrix2d.h"
#include "raccordeur_recursif_naif.h"
#include "raccordeur_recursif.h"
#include "raccordeur_iteratif.h"

void print(int * arr, int size) {
    for (int i = 0; i < size; i++) {
        std::cout  << arr[i];
        if (i != size-1)
            std::cout << " , ";
    } 
    std::cout << std::endl; 
}

int main(int argc, char **argv) {
    const int size = 5;
    MatInt2* distances = new MatInt2(size, 4);
    distances->set(0, 0, 1);distances->set(0, 1, 3);distances->set(0, 2, 2);distances->set(0, 3, 1);
    distances->set(1, 0, 2);distances->set(1, 1, 1);distances->set(1, 2, 2);distances->set(1, 3, 3);
    distances->set(2, 0, 1);distances->set(2, 1, 3);distances->set(2, 2, 4);distances->set(2, 3, 2);
    distances->set(3, 0, 2);distances->set(3, 1, 4);distances->set(3, 2, 3);distances->set(3, 3, 1);
    distances->set(4, 0, 4);distances->set(4, 1, 3);distances->set(4, 2, 1);distances->set(4, 3, 2);

    int coupeOutNaif[size];
    Raccordeur * racNaif = new RaccordeurRecursifNaif();  
    int coutTotal = racNaif->calculerRaccord(distances, coupeOutNaif);
    std::cout << "Cout total naïf: " << coutTotal << std::endl;
    std::cout << "Coupe obtenue: ";
    print(coupeOutNaif, size);
    std::cout << std::endl; 

    Raccordeur * racRecu = new RaccordeurRecursif();
    int coupeOutRecu[size];
    coutTotal = racRecu->calculerRaccord(distances, coupeOutRecu);
    std::cout << "Cout total sans calcul redondant: " << coutTotal << std::endl;
    std::cout << "Coupe obtenue: ";
    print(coupeOutNaif, size);
    std::cout << std::endl; 

    Raccordeur * racItr = new RaccordeurIteratif();
    int coupeOutItr[5];
    coutTotal = racItr->calculerRaccord(distances, coupeOutItr);
    std::cout << "Cout total iteratif avec optimisation de mémoire: " << coutTotal << std::endl;
    std::cout << "Coupe obtenue: ";
    print(coupeOutNaif, size);
    std::cout << std::endl; 

    return 0;
}