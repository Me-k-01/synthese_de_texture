#ifndef _RACCORDEUR_RECURSIF_H
#define	_RACCORDEUR_RECURSIF_H

#include "raccordeur.h"

/*!
 *
 * Cette classe est une classe concrete et derive/implemente le concept de
 * Raccordeur (\see{Raccordeur}).
 */
class RaccordeurRecursif : public Raccordeur {
    /*!
     * le calcul du raccord (\see{Raccordeur#calculerRaccord}).
     * Le code effectif se trouve dans raccordeur_recursif.cpp
     */
    private :
        int largeur;
        int hauteur;
        int * tab_cout; // Stockage des cout de coupe
        int ** tab_coupe; // Stockage des coupes minimales
        MatInt2 * distances;
    public :
        int calculerRaccord(MatInt2* distances, int * coupe) override; 
        virtual ~RaccordeurRecursif(); // destructeur
        int calculerRaccordRecu(int * coupe, const int x, const int y);
        int recuSansCalcRedondant(int * coupe, const int x, const int y); 
        //virtual int recuOptiMem(int * coupe, const int x, const int y);

};  

#endif	/* _RACCORDEUR_RECURSIF_H */

