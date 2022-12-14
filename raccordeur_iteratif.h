#ifndef _RACCORDEUR_ITERATIF_H
#define	_RACCORDEUR_ITERATIF_H

#include "raccordeur.h"

/*!
 *
 * Cette classe est une classe concrete et derive/implemente le concept de
 * Raccordeur (\see{Raccordeur}).
 */
class RaccordeurIteratif : public Raccordeur {
    /*!
     * le calcul du raccord (\see{Raccordeur#calculerRaccord}).
     * Le code effectif se trouve dans raccordeur_iteratif.cpp
     */
    private : 
        int getMinIndex(const int * const arr, const int size);
    public :
        int calculerRaccord(MatInt2* distances, int * coupe) override; 
        virtual ~RaccordeurIteratif(); // destructeur  

};  

#endif	/* _RACCORDEUR_ITERATIF_H */

