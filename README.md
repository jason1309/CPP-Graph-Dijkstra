# Chemin Optimal pour collecte de trésor - Algorithme de Dijkstra
Ce projet est un logiciel qui trouve le plus court chemin dans un univers représenté par une matrice. Le but est de déterminer le chemin le plus court permettant à un joueur de se déplacer d'une porte d'entrée, de ramasser trois trésors, et de revenir à la porte. Le calcul du chemin utilise l'algorithme de Dijkstra pour trouver le parcours optimal.

Projet réalisé pour le cours INF3105 - Structure de données (Été 2023)

## Description
Le programme reçoit en entrée un fichier `.txt` décrivant l'univers sous forme de matrice. La matrice est composée de différents terrains et coordonnées des trésors, et le programme calcule le chemin optimal en fonction des coûts de déplacement spécifiques.

### Entrées
- **Nom du fichier** : Un fichier `.txt` contenant la description de l'univers.

#### Format du fichier:

1. **Taille de l'univers** : Deux valeurs entières (largeur et hauteur) plus grnades que 1, séparées par un espace.
    - Exemple: `5 6`
2. **Matrice** : Chaque ligne représente une ligne de la matrice avec des caractères indiquant le type de terrain.
    - `N` : Plaine
    - `E` : Eau
    - `F` : Forêt
    - `R` : Route
    - `T` : Téléporte (il y a zéro ou deux téléportes sur une carte.)
    - `P` : Porte (doit apparaître qu'une seule fois.)
    - Exemple:
        ```sh
        NNNNN
        NEEFF
        RRRFF
        EENRF
        NENNR
        NPENN
        ```
3. **Coordonnées des trésors** : Trois lignes avec les coordonnées de chaque trésor (colonne et ligne).
    - Exemple:
    ```sh
    1 2
    3 0
    4 3
    ```
    Si une coordonnée n'est pas correcte, un message d'erreur est affiché et le programme se termine.

### Calcul
Le programme calcule le plus court chemin pour visiter les trois trésors et revenir à la porte en utilisant l'algorithme de Dijkstra. Le déplacement entre les cases peut être orthogonal ou diagonal, avec des coûts spécifiques selon le terrain de départ et d'arrivée  :
- Déplacement orthogonal sur `F` : 2
- Déplacement diagonal sur `F` : 2.8
- Déplacement orthogonal sur `R` à partir de `R`: 0.5
- Déplacement diagonal sur `R` à partir de `R`: 0.7
- Déplacement vers `E` : Impossible
- Déplacement entre téléportes (`T`) : 0
- Autres déplacements : 1 (orthogonal), 1.4 (diagonal)

Le programme évalue toutes les combinaisons possibles pour l'ordre de visite des trésors afin de trouver la solution optimale.

### Affichage
Le programme affiche l'ordre de parcours des trésors avec le coût du parcours pour chaque segment et le coût total. Exemple de sortie :

```sh
Porte -> T3 : 4.8
T2 -> T2 : 5.4
T2 -> T1 : 3.9
T1 -> porte : 3.8
Total : 17.9
```

## Compilation et Exécution
### Compilation
our compiler le programme, utilisez la commande `make` dans le répertoire du projet. Cela générera un exécutable nommé `TP3`.
```sh
$ make
```
### Exécution
Pour exécuter le programme avec un fichier d'exemple, utilisez la commande suivante :
```sh
$ ./TP3 <nom_du_fichier>.txt
```

Exemples:
```sh
$ ./TP3 test2.txt
Porte -> T1 : 2.0
T1 -> T2 : 1.0   
T2 -> T3 : 1.0   
T3 -> porte : 3.0
Total : 7.0      
Porte -> T3 : 3.0
T3 -> T2 : 1.0   
T2 -> T1 : 1.0   
T1 -> porte : 2.0
Total : 7.0
```

[`test2.txt`](./test2.txt) comporte deux chemins les plus courts avec la même distance. Le programme affiche tous les chemins les plus courts, lorsqu'il y a égalité.

```sh
$ ./TP3 test3.txt
Porte -> T3 : 4.8
T3 -> T2 : 5.4
T2 -> porte : 7.8
Total : 18.0
```

[`test3.txt`](./test3.txt) comporte un trésor entouré d'eau, ce dernier est alors inacessible. Le chemin résultant ne passera pas par ce trésor.