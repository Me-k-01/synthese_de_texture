
#include "raccordeur_recursif.h"
#include <cstring>
#include <limits>
#include <iostream>


int RaccordeurRecursif::calculerRaccord(MatInt2* distances, int * coupeOut) {
    const int hauteur = distances->nLignes();
    const int largeur = distances->nColonnes();



    tab_cout=new int [largeur*hauteur];
     tab_coupe= new int*[largeur*hauteur];

    for(int i=0 ; i< largeur*hauteur ; i++)
    {
        tab_cout[i]=-1;
        tab_coupe[i]=new int[hauteur];
    }
   
     

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


    delete [] tab_cout ;
    return coutMin;
} 


///a tester 
int RaccordeurRecursif::calculerRaccordRecu(MatInt2 * const distances, int * coupe, const int largeur, const int hauteur, const int x, const int y) { 

    
    if(tab_cout[x+(y*largeur)]==-1){

           

            if(y==0){
                tab_cout[x+(y*largeur)]=distances->get(x,y);
                tab_coupe[x+(y*largeur)][y]=x;
            }
            else{
                int cout_min=std::numeric_limits<int>::max();
                tab_coupe[x+(y*largeur)][y]=x;
                        
                for(int i =-1 ; i<=1 ; i++){

                    int x_suiv= x+i;

                    if(x_suiv<0 || x_suiv >=largeur) continue ;
                    
                    int cout_suiv=calculerRaccordRecu(distances,coupe,largeur,hauteur,x_suiv,y-1);

                    if(cout_suiv <= cout_min){
                        tab_cout[x+(y*largeur)]=distances->get(x,y)+cout_suiv;

                        for(int i=y-1 ; i>=0;i--){

                           tab_coupe[x+(y*largeur)][i]= coupe[i];

                        }
                       
                    }
                   
                }

            }


    }
    for(int i=y ; i>=0;i--){

        coupe[i]=tab_coupe[x+(y*largeur)][i];

    }
    return tab_cout[x+(y*largeur)];




}


RaccordeurRecursif::~RaccordeurRecursif() {
  // pas de ressources a libérer
}


/*

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
*/