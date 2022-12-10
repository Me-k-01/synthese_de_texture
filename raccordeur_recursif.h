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
        int * tab_cout;//stockage des cout de coupe
        int ** tab_coupe ;//stockage des coupes minimales
    public :
        
        int calculerRaccord(MatInt2* distances, int * coupe) override; 
        virtual ~RaccordeurRecursif(); // destructeur
        virtual int calculerRaccordRecu(MatInt2 * const distances, int * coupe, const int largeur, const int hauteur, const int x, const int y);

};  

#endif	/* _RACCORDEUR_RECURSIF_H */

