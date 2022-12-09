
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
    int coupeOut[4];
    MatInt2* distances = new MatInt2(5, 4);
    /*for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            distances->set(i, j, i+j);
        }
    } */
    distances->set(0, 0, 1);distances->set(0, 1, 3);distances->set(0, 2, 2);distances->set(0, 3, 1);
    distances->set(1, 0, 2);distances->set(1, 1, 1);distances->set(1, 2, 2);distances->set(1, 3, 3);
    distances->set(2, 0, 1);distances->set(2, 1, 3);distances->set(2, 2, 4);distances->set(2, 3, 2);
    distances->set(3, 0, 2);distances->set(3, 1, 4);distances->set(3, 2, 3);distances->set(3, 3, 1);
    distances->set(4, 0, 4);distances->set(4, 1, 3);distances->set(4, 2, 1);distances->set(4, 3, 2);

    Raccordeur * rac = new RaccordeurRecursifNaif();
    int c = rac->calculerRaccord(distances, coupeOut);
    std::cout << "cout total: " << c << std::endl;
    return 0;
}