/*
*   @author Jason Gagne - GAGJ16059700
*/

#include "Graphe.h"
#include "Point.h"
#include "Chemin.h"
#include "Traitement.h"
#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include <algorithm>

using namespace std;

/**
 * Vérifie que le nombre de paramètre soit bon et que le fichier existe.
 *
 * @param nbArgument Le nombre d'arguments passés.
 * @param argv Les arguments.
 * @return ifstream.
 */
ifstream verifierParametre(int nbArgument, char * argv []){
    if (nbArgument != 2) {
        cerr << "Erreur: Veuillez entrer seulement un fichier texte." << endl;
        exit(2);
    }
    ifstream fichierEntre(argv[1]);
    if (!fichierEntre) {
        cerr << "Erreur avec le fichier en entrée." << endl;
        exit(2);
    }

    return fichierEntre;

}

/**
 * Valide que le nombre de colonnes et le nombre de lignes inscrit sur la
 * première ligne du fichier soit supérieur a 0.
 *
 * @param nbColonnes Le nombre de colonnes.
 * @param nbLignes Le nombre de lignes.
 */
void validerTailleUnivers(int nbColonnes, int nbLignes){
    if(nbColonnes <= 1 || nbLignes <= 1){
        cerr << "Erreur: Taille de l'univers incorrect!" << endl;
        exit(1);
    }
}

/**
 * Traitement de la porte pour obtenir ses coordonnées.
 * Si elle existe déja, envoyer un message d'erreur.
 *
 * @param porte Position actuelle de la porte dans l'univers.
 * @param point Le point à vérifier comme nouvelle position de la porte.
 * @return La position de la porte.
 */
Point traiterPorte(Point &porte, Point point){
    if(porte.x == -1 && porte.y == -1){
        porte = point;
    } else {
        cerr << "Erreur: il ne peut y avoir qu'une porte dans l'univers." << endl;
        exit(1);
    }

    return porte;
}

/**
 * Ajouter un sommet au graphe de l'univers en précisant son cout orthogonal
 * ainsi que son gout diagonal selon le type de terrain.
 * 
 * Permet d'ajouter les coordonnées des téléporteurs, s'ils existent, et
 * d'envoyer un message d'erreur si trois téléporteurs sont dans l'univers. 
 *
 * Appel de la méthode traiterPorte lorsqu'on atteint la porte.
 * 
 * @param univers Univers dans lequel ajouter le sommet.
 * @param typeTerrain Le type de terrain à associer au sommet.
 * @param x La coordonnée x.
 * @param y La coordonnée y.
 * @param porte Position de la porte dans l'univers.
 * @param T1 Position du premier téléporteur dans l'univers.
 * @param T2 Position du deuxième téléporteur dans l'univers.
 */
void ajouterUnSommet(Graphe<Point>& univers, char typeTerrain, int x, int y, Point &porte, Point &T1, Point &T2){
    double coutOrthogonal = 1.0;
    double coutDiagonal = 1.4;
    Point point(x,y);

    if(typeTerrain == 'F'){
        coutOrthogonal = 2.0;
        coutDiagonal = 2.8;
    } else if(typeTerrain == 'R'){
        coutDiagonal = 0.7;
        coutOrthogonal = 0.5;
    } else if(typeTerrain == 'E'){
        coutDiagonal = -1;
        coutOrthogonal = -1;
    } else if(typeTerrain == 'P'){
        point = traiterPorte(porte, point);
    } else if(typeTerrain == 'T'){
        if(T1.x == -1 && T1.y == -1){
            T1 = point;
        } else if(T2.x == -1 && T2.y == -1){
            T2 = point;
        } else {
            cerr << "Erreur: il doit y avoir 0 ou 2 teleporteur." << endl;
            exit(1);
        }
    }    
    univers.ajouterSommet(point, typeTerrain, coutOrthogonal, coutDiagonal);
}

/**
 * Construit et retourne un graphe représentant l'univers selon le fichier en entrée.
 *
 * @param fichierEntre Fichier d'entrée contenant les informations de l'univers.
 * @param nbColonnes Nombre de colonnes de l'univers.
 * @param nbLignes Nombre de lignes de l'univers.
 * @param porte Position de la porte dans l'univers.
 * @param T1 Position du premier téléporteur dans l'univers.
 * @param T2 Position du deuxième téléporteur dans l'univers.
 * @return Le graphe représentant l'univers.
 */
Graphe<Point> construireUnivers(ifstream& fichierEntre, int nbColonnes, int nbLignes, Point &porte, Point &T1, Point &T2){
    Graphe<Point> univers;
    for(int y=0; y < nbLignes; y++){
        for(int x=0; x < nbColonnes; x++){
            char typeTerrain;
            fichierEntre >> typeTerrain;
            ajouterUnSommet(univers, typeTerrain, x, y, porte, T1, T2);
        }
    }

    return univers;
}

/**
 * Passe au travers de la matrice complete et ajoute les voisins orthogonaux
 * et les voisins diagonales. S'assure de ne pas depasser les limites de la 
 * mattrice.
 *
 * @param univers Graphe représentant l'univers.
 * @param nbColonnes Nombre de colonnes de l'univers.
 * @param nbLignes Nombre de lignes de l'univers.
 */
void ajouterLesVoisins(Graphe<Point>& univers, int nbColonnes, int nbLignes){
    for(int y=0; y < nbLignes; y++){
        for(int x=0; x < nbColonnes; x++){
            Point pointActuel(x,y);
            
            if(y+1 < nbLignes){
                univers.ajouterAreteNonOrienteeOrthogonal(pointActuel, Point(x, y+1)); 
            }

            if(x+1 < nbColonnes){
                univers.ajouterAreteNonOrienteeOrthogonal(pointActuel, Point(x+1, y));
            }

            if(x+1 < nbColonnes && y+1 < nbLignes){
                univers.ajouterAreteNonOrienteeDiagonal(pointActuel, Point(x+1, y+1));
            }

            if(x+1 < nbColonnes && y-1 >= 0){
                univers.ajouterAreteNonOrienteeDiagonal(pointActuel, Point(x+1, y-1)); // 4,2
            }
            if(x-1 >= 0 && y+1 < nbLignes){
                univers.ajouterAreteNonOrienteeDiagonal(pointActuel, Point(x-1, y+1));
            }
        }
    }
}

/**
 * Vérifie si la porte est valide, c'est-à-dire si elle existe et n'est pas entourée d'eau.
 * Envoie un message d'erreur et quitte le programme si elle n'est pas valide.
 *
 * @param univers Le graphe représentant l'univers.
 * @param porte La position de la porte.
 */
void verifierPorteValide(Graphe<Point> univers, Point porte){
    set<Point> listeVoisins = univers.obtenirVoisins(porte);
    if(porte.x == -1 && porte.y == -1){
        cerr << "Erreur: il doit y avoir une porte dans l'univers." << endl;
        exit(1);
    }

    if(listeVoisins.empty()){
        cerr << "Erreur: la porte est entouré d'eau. Aucun chemin valide." << endl;
        exit(1);
    }
}

Point obtenirCoordonneTresor(ifstream& fichierEntre, int nbLignes, int nbColonnes){
    int x,y; 
    fichierEntre >> x;
    fichierEntre >> y;

    if(x >= nbColonnes || y >= nbColonnes || x < 0 || y < 0){
        cerr << "Erreur: les coordonnées d'un trésor sont invalides." << endl;
        exit(1);
    }

    return Point(x,y);
}


/**
 * Compare deux chemins en fonction de leur distance totale par rapport à la porte.
 *
 * @param chemin1 Le premier chemin à comparer.
 * @param chemin2 Le deuxième chemin à comparer.
 * @return Vrai si le chemin1 a une distance totale inférieure au chemin2, sinon faux.
 */
bool trierChemins(const Chemin& chemin1, const Chemin& chemin2) {
    return chemin1.obtenirDistanceTotal("Porte") < chemin2.obtenirDistanceTotal("Porte");
}

/**
 * Traite les téléporteurs en ajoutant une arête non orientée entre eux s'ils sont tous les deux présents.
 * Génère une erreur si un seul téléporteur est présent, car il doit y en avoir zéro ou deux.
 *
 * @param univers Le graphe représentant l'univers.
 * @param T1 Le premier téléporteur.
 * @param T2 Le deuxième téléporteur.
 */
void traiterTeleporteur(Graphe<Point> &univers, Point &T1, Point &T2){
    if(T1.x != -1 && T1.y != -1 && T2.x == -1 && T2.y == -1){
        cerr << "Erreur: Il ne peut pas avoir qu'un seul teleporteur." << endl;
        exit(1);
    } else if( T1.x != -1 && T2.x != -1){
        univers.ajouterAreteNonOrienteeOrthogonal(T1, T2);
    }
}

/**
 * Affiche les chemins avec la distance la plus basse.
 * Si plusieurs ont la distance la plus basse, ils sont tous afficher.
 *
 * @param chemins Le vecteur contenant les chemins à afficher.
 */
void afficherLesResultats(vector<Chemin> &chemins){
    sort(chemins.begin(), chemins.end(), trierChemins);
    double distanceMin = chemins.at(0).obtenirDistanceTotal("Porte"); 
    for( const Chemin& chemin : chemins){
        double distanceCourante = chemin.obtenirDistanceTotal("Porte");
        if(distanceCourante == distanceMin){
            chemin.afficherChemin("Porte");
        }
        
    }
}

int main(int argc, char * argv []) {
    int nbColonnes, nbLignes;
    Point porte(-1,-1);
    Point T1(-1,-1);
    Point T2(-1,-1);
    Point tresor1(-1,-1);
    Point tresor2(-1,-1);
    Point tresor3(-1,-1);

    ifstream fichierEntre = verifierParametre(argc, argv);

    fichierEntre >> nbColonnes >> nbLignes;
    validerTailleUnivers(nbColonnes, nbLignes);

    //Permet aussi de trouver la porte et les teleporteurs
    Graphe<Point> univers = construireUnivers(fichierEntre, nbColonnes, nbLignes, porte, T1, T2);
    traiterTeleporteur(univers, T1, T2);
    ajouterLesVoisins(univers, nbColonnes, nbLignes);

    //Verifie qu'il existe bien une porte et qu'elle n'est pas entoure d'eau
    verifierPorteValide(univers, porte);

    tresor1 = obtenirCoordonneTresor(fichierEntre, nbLignes, nbColonnes);
    tresor2 = obtenirCoordonneTresor(fichierEntre, nbLignes, nbColonnes);
    tresor3 = obtenirCoordonneTresor(fichierEntre, nbLignes, nbColonnes);
    
    Traitement traitementChemins;
    vector<Chemin> chemins = traitementChemins.calculerChemins(univers, porte, tresor1, tresor2, tresor3);
    
    afficherLesResultats(chemins);

    fichierEntre.close();
    return 0;
}