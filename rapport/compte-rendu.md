# 2 Problème posé

# 3 Critère d’erreur

# 4 Coupe optimale

# 5 Travail demandé

### 2. Impl ́ementez une variante de l’algorithme (a). Un g ́en ́erateur al ́eatoire de permutation de blocs permet d’ ́equilibrer le nombre d’occurences de chaque bloc.
cf "permuteur.cpp" pour voir le fonctionnement de la focntion de permutation


### 3. 
> Que représente e[i, j]:?
e[i, j] est l'erreur entre les deux pixels de coordonnées i et j qui se chevauchent. Ils appartiennent aux bandes de recouvrement des deux blocs.
Elle est calculé en faisant la norme 2 des écarts sur les canaux RGB de ces deux pixels
> Que représente E?
C'est le critère d'erreur entre deux bandes, qui est défini par la somme des erreurs de chaque pixels. 

### 4. Quel est le rapport entre le coût de la coupe optimale et les Eij ?
Le coût de la coupe optimale correspond à la somme de la norme des écarts RGB sur le chemin minimals
Donc E[i,j] est égal au coût de la coupe optimale de la ligne 0 à i.


### 5. Clarifiez la notion de coupe optimale sur l’exemple suivant:
Pour une découpe vertical sur la matrice des erreurs e:
![Decoupe verticale](./rapport/decoupe_verticale.jpg)
On choisit la première valeur puis on stocke dans differents tableau les valeurs de la ligne au-dessus et on répète l'opération jusqu'à la dernière ligne. Cela va nous creer de nombreux tableaux que nous parcourerons pour obtenir le chemin minimal à partir de l'origine choisi. Et afin d'obtenir le plus court, il nous faudra répeter ces opérations autant de fois que la largeur de la bande, ici 4 fois.
On obtient comme coupe optimale si l'origine est:
    -4: 4;2;1;2;1 =10
    -3: 3;2;1;2;1 =9
    -1: 1;1;2;2;1 =7
    -2: 2;1;2;2;1 =8
Ce qui nous donne le cout de coupe optimale le plus faible égale à 7 en passant par(de bas en haut):1;1;2;2;1.


### 6. Estimez la complexité d’une solution récursive naive pour le calcul de la coupe optimale.
O(i * 3^j)    teta(i*j)


### 7. Implementez une solution recursive sans calcul redondant.
cf "raccordeur_recursif.cpp" -> actuellement uniquevement version recursif AVEC calcul redondant


### 8. Implementez une solution itérative.
cf "raccordeur_iteratif.cpp" -> actuellement inexistant

### 9. Question complementaire : quelle est la complexité globale de l’algorithme (c) en prenant en compte tous les paramètres ?

# 6 Dossier a rendre