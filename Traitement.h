#if !defined(__TRAITEMENT_H__)
#define __TRAITEMENT_H__

#include "Chemin.h"
#include <vector>
#include "Graphe.h"

class Traitement{
    public:
    vector<Chemin> calculerChemins(const Graphe<Point> univers, Point porte, Point tresor1, Point tresor2, Point tresor3);

    private:
        bool verifierTresorAccessible(Graphe<Point> univers, Point tresor);
        void validerCheminPorteTresor(double distanceTresor1, double distanceTresor2, double distanceTresor3);
};

/**
 * Obtient les coordonnées d'un trésor à partir du fichier d'entrée.
 * Vérifie également si les coordonnées sont valides et affiche un message d'erreur en cas d'erreur.
 *
 * @param fichierEntre Le fichier.
 * @param nbLignes Nombre de lignes dans l'univers.
 * @param nbColonnes Nombre de colonnes dans l'univers.
 * @return Les coordonnées du trésor.
 */
bool Traitement::verifierTresorAccessible(Graphe<Point> univers, Point tresor){
    bool accessible = true;
    set<Point> listeVoisins = univers.obtenirVoisins(tresor);

    if(listeVoisins.empty()){
        accessible = false;
    }

    if(univers.obtenirTypeTerrain(tresor) == 'E'){
        cerr << "Erreur: un trésor se trouve dans l'eau." << endl;
        exit(1);
    }

    return accessible;
}

/**
 * Valide qu'il y ait, au minimum, un trésor d'accessible.
 * Si toutes les distances sont egale a 0, aucun trésor n'est accessible.
 * Envoie d'un message d'erreur suivi de l'arrêt du programme.
 * 
 * @param distanceTresor1 Distance entre la porte et le trésor 1.
 * @param distanceTresor2 Distance entre la porte et le trésor 2.
 * @param distanceTresor3 Distance entre la porte et le trésor 3.
 */
void Traitement::validerCheminPorteTresor(double distanceTresor1, double distanceTresor2, double distanceTresor3){
    if(distanceTresor1 == 0 && distanceTresor2 == 0 && distanceTresor3 == 0){
        cerr << "Erreur: Aucun trésor accessible." << endl;
        exit(1);
    }
}

vector<Chemin> Traitement::calculerChemins(Graphe<Point> univers, Point porte, Point tresor1, Point tresor2, Point tresor3){
    vector<Chemin> chemins;

    bool tresor1Accessible = verifierTresorAccessible(univers, tresor1);
    bool tresor2Accessible = verifierTresorAccessible(univers, tresor2);
    bool tresor3Accessible = verifierTresorAccessible(univers, tresor3);
    
    univers.calculerPlusPetitChemin(porte);
    double distancePorteTresor1 = univers.obtenirDistanceMin(tresor1);
    double distancePorteTresor2 = univers.obtenirDistanceMin(tresor2);
    double distancePorteTresor3 = univers.obtenirDistanceMin(tresor3);
    validerCheminPorteTresor(distancePorteTresor1, distancePorteTresor2, distancePorteTresor3);

    univers.calculerPlusPetitChemin(tresor1);
    double distanceTresor1Porte = univers.obtenirDistanceMin(porte);
    double distanceTresor1Tresor2 = univers.obtenirDistanceMin(tresor2);
    double distanceTresor1Tresor3 = univers.obtenirDistanceMin(tresor3);

    univers.calculerPlusPetitChemin(tresor2);
    double distanceTresor2Porte = univers.obtenirDistanceMin(porte);
    double distanceTresor2Tresor1 = univers.obtenirDistanceMin(tresor1);
    double distanceTresor2Tresor3 = univers.obtenirDistanceMin(tresor3);

    univers.calculerPlusPetitChemin(tresor3);
    double distanceTresor3Porte = univers.obtenirDistanceMin(porte);
    double distanceTresor3Tresor1 = univers.obtenirDistanceMin(tresor1);
    double distanceTresor3Tresor2 = univers.obtenirDistanceMin(tresor2);

    if(tresor1Accessible && tresor2Accessible && tresor3Accessible){
        Chemin ordre123;
        Chemin ordre132;
        Chemin ordre213;
        Chemin ordre231;
        Chemin ordre312;
        Chemin ordre321;

        ordre123.ajouterSommet("Porte",0);
        ordre123.ajouterSommet("T1", distancePorteTresor1);
        ordre123.ajouterSommet("T2", distanceTresor1Tresor2);
        ordre123.ajouterSommet("T3", distanceTresor2Tresor3);
        ordre123.ajouterSommet("porte", distanceTresor3Porte);
        ordre123.ajouterAreteOrientee("Porte", "T1");
        ordre123.ajouterAreteOrientee("T1", "T2");
        ordre123.ajouterAreteOrientee("T2", "T3");
        ordre123.ajouterAreteOrientee("T3", "porte");

        ordre132.ajouterSommet("Porte",0);
        ordre132.ajouterSommet("T1", distancePorteTresor1);
        ordre132.ajouterSommet("T3", distanceTresor1Tresor3);
        ordre132.ajouterSommet("T2", distanceTresor3Tresor2);
        ordre132.ajouterSommet("porte", distanceTresor2Porte);
        ordre132.ajouterAreteOrientee("Porte", "T1");
        ordre132.ajouterAreteOrientee("T1", "T3");
        ordre132.ajouterAreteOrientee("T3", "T2");
        ordre132.ajouterAreteOrientee("T2", "porte");
        
        ordre213.ajouterSommet("Porte",0);
        ordre213.ajouterSommet("T2", distancePorteTresor2);
        ordre213.ajouterSommet("T1", distanceTresor2Tresor1);
        ordre213.ajouterSommet("T3", distanceTresor1Tresor3);
        ordre213.ajouterSommet("porte", distanceTresor3Porte);
        ordre213.ajouterAreteOrientee("Porte", "T2");
        ordre213.ajouterAreteOrientee("T2", "T1");
        ordre213.ajouterAreteOrientee("T1", "T3");
        ordre213.ajouterAreteOrientee("T3", "porte");

        ordre231.ajouterSommet("Porte",0);
        ordre231.ajouterSommet("T2", distancePorteTresor2);
        ordre231.ajouterSommet("T3", distanceTresor2Tresor3);
        ordre231.ajouterSommet("T1", distanceTresor3Tresor1);
        ordre231.ajouterSommet("porte", distanceTresor1Porte);
        ordre231.ajouterAreteOrientee("Porte", "T2");
        ordre231.ajouterAreteOrientee("T2", "T3");
        ordre231.ajouterAreteOrientee("T3", "T1");
        ordre231.ajouterAreteOrientee("T1", "porte");

        ordre312.ajouterSommet("Porte",0);
        ordre312.ajouterSommet("T3", distancePorteTresor3);
        ordre312.ajouterSommet("T1", distanceTresor3Tresor1);
        ordre312.ajouterSommet("T2", distanceTresor1Tresor2);
        ordre312.ajouterSommet("porte", distanceTresor2Porte);
        ordre312.ajouterAreteOrientee("Porte", "T3");
        ordre312.ajouterAreteOrientee("T3", "T1");
        ordre312.ajouterAreteOrientee("T1", "T2");
        ordre312.ajouterAreteOrientee("T2", "porte");

        ordre321.ajouterSommet("Porte",0);
        ordre321.ajouterSommet("T3", distancePorteTresor3);
        ordre321.ajouterSommet("T2", distanceTresor3Tresor2);
        ordre321.ajouterSommet("T1", distanceTresor2Tresor1);
        ordre321.ajouterSommet("porte", distanceTresor1Porte);

        ordre321.ajouterAreteOrientee("Porte", "T3");
        ordre321.ajouterAreteOrientee("T3", "T2");
        ordre321.ajouterAreteOrientee("T2", "T1");
        ordre321.ajouterAreteOrientee("T1", "porte");

        chemins.push_back(ordre123);
        chemins.push_back(ordre132);
        chemins.push_back(ordre213);
        chemins.push_back(ordre231);
        chemins.push_back(ordre312);
        chemins.push_back(ordre321);
    } else if(!tresor1Accessible && tresor2Accessible && tresor3Accessible){
        Chemin ordre23;
        Chemin ordre32;

        ordre23.ajouterSommet("Porte",0);
        ordre23.ajouterSommet("T2", distancePorteTresor2);
        ordre23.ajouterSommet("T3", distanceTresor2Tresor3);
        ordre23.ajouterSommet("porte", distanceTresor3Porte);
        ordre23.ajouterAreteOrientee("Porte", "T2");
        ordre23.ajouterAreteOrientee("T2", "T3");
        ordre23.ajouterAreteOrientee("T3", "porte");

        ordre32.ajouterSommet("Porte",0);
        ordre32.ajouterSommet("T3", distancePorteTresor3);
        ordre32.ajouterSommet("T2", distanceTresor3Tresor2);
        ordre32.ajouterSommet("porte", distanceTresor2Porte);
        ordre32.ajouterAreteOrientee("Porte", "T3");
        ordre32.ajouterAreteOrientee("T3", "T2");
        ordre32.ajouterAreteOrientee("T2", "porte");

        chemins.push_back(ordre23);
        chemins.push_back(ordre32);
    } else if(tresor1Accessible && !tresor2Accessible && tresor3Accessible){
        Chemin ordre13;
        Chemin ordre31;

        ordre13.ajouterSommet("Porte",0);
        ordre13.ajouterSommet("T1", distancePorteTresor1);
        ordre13.ajouterSommet("T3", distanceTresor1Tresor3);
        ordre13.ajouterSommet("porte", distanceTresor3Porte);
        ordre13.ajouterAreteOrientee("Porte", "T1");
        ordre13.ajouterAreteOrientee("T1", "T3");
        ordre13.ajouterAreteOrientee("T3", "porte");

        ordre31.ajouterSommet("Porte",0);
        ordre31.ajouterSommet("T3", distancePorteTresor3);
        ordre31.ajouterSommet("T1", distanceTresor3Tresor1);
        ordre31.ajouterSommet("porte", distanceTresor1Porte);
        ordre31.ajouterAreteOrientee("Porte", "T3");
        ordre31.ajouterAreteOrientee("T3", "T1");
        ordre31.ajouterAreteOrientee("T1", "porte");

        chemins.push_back(ordre13);
        chemins.push_back(ordre31);
    } else if(tresor1Accessible && tresor2Accessible && !tresor3Accessible){
        Chemin ordre12;
        Chemin ordre21;

        ordre12.ajouterSommet("Porte",0);
        ordre12.ajouterSommet("T1", distancePorteTresor1);
        ordre12.ajouterSommet("T2", distanceTresor1Tresor2);
        ordre12.ajouterSommet("porte", distanceTresor2Porte);
        ordre12.ajouterAreteOrientee("Porte", "T1");
        ordre12.ajouterAreteOrientee("T1", "T2");
        ordre12.ajouterAreteOrientee("T2", "porte");

        ordre21.ajouterSommet("Porte",0);
        ordre21.ajouterSommet("T2", distancePorteTresor2);
        ordre21.ajouterSommet("T1", distanceTresor2Tresor1);
        ordre21.ajouterSommet("porte", distanceTresor1Porte);
        ordre21.ajouterAreteOrientee("Porte", "T2");
        ordre21.ajouterAreteOrientee("T2", "T1");
        ordre21.ajouterAreteOrientee("T1", "porte");

        chemins.push_back(ordre12);
        chemins.push_back(ordre21);
    } else if(!tresor1Accessible && !tresor2Accessible && tresor3Accessible){
        Chemin ordre3;
        ordre3.ajouterSommet("Porte",0);
        ordre3.ajouterSommet("T3", distancePorteTresor3);
        ordre3.ajouterSommet("porte", distanceTresor3Porte);
        ordre3.ajouterAreteOrientee("Porte", "T3");
        ordre3.ajouterAreteOrientee("T3", "porte");

        chemins.push_back(ordre3);
    } else if(tresor1Accessible && !tresor2Accessible && !tresor3Accessible){
        Chemin ordre1;
        ordre1.ajouterSommet("Porte",0);
        ordre1.ajouterSommet("T1", distancePorteTresor1);
        ordre1.ajouterSommet("porte", distanceTresor1Porte);
        ordre1.ajouterAreteOrientee("Porte", "T1");
        ordre1.ajouterAreteOrientee("T1", "porte");

        chemins.push_back(ordre1);
    } else if(!tresor1Accessible && tresor2Accessible && !tresor3Accessible){
        Chemin ordre2;
        ordre2.ajouterSommet("Porte",0);
        ordre2.ajouterSommet("T2", distancePorteTresor2);
        ordre2.ajouterSommet("porte", distanceTresor2Porte);
        ordre2.ajouterAreteOrientee("Porte", "T2");
        ordre2.ajouterAreteOrientee("T2", "porte");

        chemins.push_back(ordre2);
    }

    return chemins;
}

#endif