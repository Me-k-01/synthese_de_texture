# Projet de synthèse de texture en c++ (2022-2023)

Ce projet réalisé dans le cadre de l'UE Algorithmique et Programmation Avancée du master informatique de Limoges.
Trois étudiants ont participés a ce projet:
- Florian AUBERVAL
- Romain SIAUDEAU
- Timothée BEHUET

Pour compiler le programme:
```sh
make tp
```

Pour executer le programme:
```sh
./tp ./img.png numero_algo
```


Test du raccordeur sur l'exemple du tp:
```sh
g++ -Wall -o test test_raccordeur.cpp matrix2d.cpp raccordeur_recursif_naif.cpp raccordeur_recursif.cpp raccordeur_iteratif.cpp && ./test
```

Benchmark des algoritmes:  
```sh
python ./benchmark.py
```
Avant d'executer le benchmark, il faut retirer tous les screen->Click(); dans textureur.cpp, afin d'éviter de bloquer la sortie du script
