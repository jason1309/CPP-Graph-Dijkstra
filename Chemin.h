#if !defined(__CHEMIN_H__)
#define __CHEMIN_H__

#include "Point.h"
#include <string>
#include <set>
#include <map>
#include <iostream>
#include <iomanip>

using namespace std;

class Chemin {
public:
    void ajouterSommet(const string& s, double distance);
    double obtenirDistanceTotal(const string& sommet) const;
    void ajouterAreteOrientee(const string& s1, const string& s2);
    void afficherChemin(const string& sommet) const;
    void afficherVoisinsRecursif(const string& sommet) const;
    
    

private:
    struct Sommet {
        string voisin;
        string affichage;
        double distance;
    };
    map<string, Sommet> sommets;
};

void Chemin::ajouterSommet(const string& s, double distance) {
    sommets[s];
    sommets[s].distance = distance;
}

void Chemin::ajouterAreteOrientee(const string& s1, const string& s2) {
    sommets[s1].voisin = s2;
}

double Chemin::obtenirDistanceTotal(const string& sommet) const {
    double distanceResultat = sommets.at(sommet).distance;

    const string& voisin = sommets.at(sommet).voisin;
    if (!voisin.empty()) {
        distanceResultat += obtenirDistanceTotal(voisin);
    }

    return distanceResultat;
}

void Chemin::afficherVoisinsRecursif(const string& sommet) const{
    if( sommet != "porte"){
    cout << sommet << " : " << fixed << setprecision(1) << sommets.at(sommet).distance << endl;
    afficherChemin(sommet);
    } else if(sommet == "porte"){
        cout << "porte : " << fixed << setprecision(1) << sommets.at(sommet).distance << endl;
    } else {
        return;
    }
    
}

void Chemin::afficherChemin(const string& sommet) const {
    cout << sommet << " -> ";
    afficherVoisinsRecursif(sommets.at(sommet).voisin);
    if(sommets.at(sommet).voisin == "porte"){
    cout << "Total : " << fixed << setprecision(1) << obtenirDistanceTotal("Porte") << endl;
    }
}


#endif
