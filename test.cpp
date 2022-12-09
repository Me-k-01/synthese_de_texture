// g++ -Wall -o test test.cpp matrix2d.cpp raccordeur_recursif.cpp && ./test
#include <iostream>
#include "matrix2d.h"
#include "raccordeur_recursif.h"

void f(int * arr) {
    arr[0] = 1;
}

int main(int argc, char **argv) {
    /*int arr[2];
    arr[0] = 0;
    arr[1] = 0;
    f(arr);

    std::cout << "arr[0] = " << arr[0] << std::endl;*/
    int coupeOut[5];
    MatInt2* distances = new MatInt2(5, 4);
    distances->set(0, 0, 1);distances->set(0, 1, 3);distances->set(0, 2, 2);distances->set(0, 3, 1);
    distances->set(1, 0, 2);distances->set(1, 1, 1);distances->set(1, 2, 2);distances->set(1, 3, 3);
    distances->set(2, 0, 1);distances->set(2, 1, 3);distances->set(2, 2, 4);distances->set(2, 3, 2);
    distances->set(3, 0, 2);distances->set(3, 1, 4);distances->set(3, 2, 3);distances->set(3, 3, 1);
    distances->set(4, 0, 4);distances->set(4, 1, 3);distances->set(4, 2, 1);distances->set(4, 3, 2);

    Raccordeur * rac = new RaccordeurRecursifNaif();
    int coutTotal = rac->calculerRaccord(distances, coupeOut);
    std::cout << "cout total: " << coutTotal << std::endl;
    std::cout << "coupe: ";
    for (int i = 0; i < 5; i++) {
        std::cout  << coupeOut[i] << " , " ;
    } 
    std::cout << std::endl; 
    return 0;
}