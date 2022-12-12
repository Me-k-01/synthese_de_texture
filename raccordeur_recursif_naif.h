#ifndef _RACCORDEUR_RECURSIF_NAIF_H
#define	_RACCORDEUR_RECURSIF_NAIF_H

#include "raccordeur.h"

/*!
 *
 * Cette classe est une classe concrete et derive/implemente le concept de
 * Raccordeur (\see{Raccordeur}).
 */
class RaccordeurRecursifNaif : public Raccordeur {
    /*!
     * le calcul du raccord (\see{Raccordeur#calculerRaccord}).
     * Le code effectif se trouve dans raccordeur_recursif_naif.cpp
     */
    private:
        MatInt2 * distances;
        int largeur;
        int hauteur;
        int calculerRaccordRecu(int * coupe, const int x, const int y);
    public :        
        int calculerRaccord(MatInt2* distances, int * coupe) override; 
        virtual ~RaccordeurRecursifNaif(); // destructeur 
};  

#endif	/* _RACCORDEUR_RECURSIF_NAIF_H */

