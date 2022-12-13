import subprocess
from time import time

# A faire avant de lancer la benchmark: 
# Il faut retirer tous les screen->Click(); dans textureur.cpp, afin d'éviter de bloquer la sortie   

def chrono(num):
    now = time()

    # Lancer le processus
    subprocess.run(["./tp", "./gravier.tif", str(num)])   
    return time() - now


arr = []

for i in range(6):
    if i != 3 : # On skip l'algo recu naif
        arr.append(chrono(i)) 
    else :  
        arr.append(-1)


for i in range(len(arr)):
    print("chrono(",i, "): ", arr[i]," ms")