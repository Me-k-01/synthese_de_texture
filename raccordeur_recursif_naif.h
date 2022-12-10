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
    int calculerRaccord(MatInt2* distances, int * coupe) override; 
    virtual ~RaccordeurRecursifNaif(); // destructeur
    virtual int calculerRaccordRecu(MatInt2 * const distances, int * coupe, const int largeur, const int hauteur, const int x, const int y);

};  

#endif	/* _RACCORDEUR_RECURSIF_NAIF_H */

