#if !defined(__GRAPHE_H__)
#define __GRAPHE_H__

#include <queue>
#include <map>
#include <set>
#include <iostream>
#include <limits>
#include "Point.h"

using namespace std;
template <class S>
class Graphe{
    public:
        void ajouterSommet(const S& s, char typeTerrain, const double coutOrthogonal, 
                           const double coutDiagonal);
        void ajouterAreteOrienteeDiagonal(const S& s1, const S& s2);
        void ajouterAreteNonOrienteeDiagonal(const S& s1, const S& s2);
        void ajouterAreteOrienteeOrthogonal(const S& s1, const S& s2);
        void ajouterAreteNonOrienteeOrthogonal(const S& s1, const S& s2);
        void afficherContenuGraphe();
        set<S> obtenirVoisins(const S& sommet);
        void calculerPlusPetitChemin(const S& sommet);
        double obtenirTypeTerrain(const S& sommet);

        double obtenirDistanceMin(const S& sommet);
        
        
    private:
        struct Sommet{
            char typeTerrain;
            set<S> voisinsOrthogonal;
            set<S> voisinsDiagonal;

            double coutOrthogonal;
            double coutDiagonal;
            double coutTP;

        };
        map<S, Sommet> sommets;
        map<S, double> distance;
        map<S, S> provenance;

        struct SommetDistance {
            S sommet;
            double distance;

            bool operator<(const SommetDistance& autre) const {
                return distance > autre.distance;
            }
        };
        
};


template <class S>
void Graphe<S>::ajouterSommet(const S& s, char typeTerrain, const double coutOrthogonal, 
                              const double coutDiagonal){
    sommets[s]; 
    sommets[s].typeTerrain = typeTerrain;
    sommets[s].coutOrthogonal = coutOrthogonal;
    sommets[s].coutDiagonal = coutDiagonal;

}


template <class S>
void Graphe<S>::ajouterAreteNonOrienteeDiagonal(const S& s1, const S& s2){
    if(sommets[s1].typeTerrain != 'E' && sommets[s2].typeTerrain != 'E'){
        ajouterAreteOrienteeDiagonal(s1,s2);
        ajouterAreteOrienteeDiagonal(s2,s1);
    }
}

template <class S>
void Graphe<S>::ajouterAreteOrienteeDiagonal(const S& s1, const S& s2){
    sommets[s1].voisinsDiagonal.insert(s2);
}

template <class S>
void Graphe<S>::ajouterAreteNonOrienteeOrthogonal(const S& s1, const S& s2){
    if(sommets[s1].typeTerrain != 'E' && sommets[s2].typeTerrain != 'E'){
        ajouterAreteOrienteeOrthogonal(s1,s2);
        ajouterAreteOrienteeOrthogonal(s2,s1);
    }
}

template <class S>
void Graphe<S>::ajouterAreteOrienteeOrthogonal(const S& s1, const S& s2){
    sommets[s1].voisinsOrthogonal.insert(s2);
}

template <class S>
set<S> Graphe<S>::obtenirVoisins(const S& sommet){
    const set<S>& voisinsDiagonal = sommets[sommet].voisinsDiagonal;
    const set<S>& voisinsOrthogonal = sommets[sommet].voisinsOrthogonal;

    set<S> voisinsDiagonalEtOrthogonal = voisinsDiagonal;
    voisinsDiagonalEtOrthogonal.insert(voisinsOrthogonal.begin(), voisinsOrthogonal.end());

    return voisinsDiagonalEtOrthogonal;
}

template <class S>
void Graphe<S>::calculerPlusPetitChemin(const S& sommet){
    Point pointInexistant(-1,-1);
    for(const auto& pair : sommets){
        distance[pair.first] = numeric_limits<double>::max();
        provenance[pair.first] = pointInexistant;
    }

    distance[sommet] = 0;

    priority_queue <SommetDistance> distanceMin;
    for(const auto& pair : distance){
        const S& sommet = pair.first;
        double dist = pair.second;
        distanceMin.push({sommet, dist});
    }
    while(!distanceMin.empty()){
        SommetDistance u = distanceMin.top();
        distanceMin.pop();

        S sommetCourant = u.sommet;
        double distanceCourante = u.distance;
 
        Sommet& sommetCourantInfo = sommets[sommetCourant];

        for(const S& voisin : sommetCourantInfo.voisinsDiagonal){
            Sommet& sommetVoisinInfo = sommets[voisin];
            
            if(sommetVoisinInfo.typeTerrain == 'F'){
                if(distanceCourante + sommetVoisinInfo.coutDiagonal < distance[voisin]){
                    distance[voisin] = distanceCourante + sommetVoisinInfo.coutDiagonal;
                    distanceMin.push({voisin, distanceCourante + sommetVoisinInfo.coutDiagonal});
                }
            } else if(sommetCourantInfo.typeTerrain == 'R' && sommetVoisinInfo.typeTerrain == 'R'){
                if(distanceCourante + sommetVoisinInfo.coutDiagonal < distance[voisin]){
                    distance[voisin] = distanceCourante + sommetVoisinInfo.coutDiagonal;
                    distanceMin.push({voisin, distanceCourante + sommetVoisinInfo.coutDiagonal});
                }
            } else {
                if(distanceCourante + 1.4 < distance[voisin]){
                    distance[voisin] = distanceCourante + 1.4;
                    distanceMin.push({voisin, distanceCourante + 1.4});
                }
            }

        }

        for(const S& voisin : sommetCourantInfo.voisinsOrthogonal){
            Sommet& sommetVoisinInfo = sommets[voisin];
            
            if(sommetVoisinInfo.typeTerrain == 'F'){
                if(distanceCourante + sommetVoisinInfo.coutOrthogonal < distance[voisin]){
                    distance[voisin] = distanceCourante + sommetVoisinInfo.coutOrthogonal;
                    distanceMin.push({voisin, distanceCourante + sommetVoisinInfo.coutOrthogonal});
                }
            } else if(sommetCourantInfo.typeTerrain == 'R' && sommetVoisinInfo.typeTerrain == 'R'){
                if(distanceCourante + sommetVoisinInfo.coutOrthogonal < distance[voisin]){
                    distance[voisin] = distanceCourante + sommetVoisinInfo.coutOrthogonal;
                    distanceMin.push({voisin, distanceCourante + sommetVoisinInfo.coutOrthogonal});
                }
            } else if(sommetCourantInfo.typeTerrain == 'T' && sommetVoisinInfo.typeTerrain == 'T') {
                if(distanceCourante + 0 < distance[voisin]){
                    distance[voisin] = distanceCourante + 0;
                    distanceMin.push({voisin, distanceCourante + 0});
                }
            } else {
                if(distanceCourante + 1.0 < distance[voisin]){
                    distance[voisin] = distanceCourante + 1.0;
                    distanceMin.push({voisin, distanceCourante + 1.0});
                }
            }

        }
    }
}

template <class S>
double Graphe<S>::obtenirDistanceMin(const S& sommet){
    double distanceResultat;
    if(distance.find(sommet) != distance.end()){
        distanceResultat = distance[sommet];
    } 

    if(distanceResultat >= numeric_limits<double>::max()){
        distanceResultat = 0.0;
    }

    return distanceResultat;
}

template <class S>
double Graphe<S>::obtenirTypeTerrain(const S& sommet){
    return sommets[sommet].typeTerrain;
}

template <class S>
void Graphe<S>::afficherContenuGraphe() {
    for (const auto& pair : sommets) {
        const typename Graphe<S>::Sommet& sommet = pair.second;
        const S& sommetId = pair.first;
        cout << endl;
        cout << "Le x: " << sommetId.x << " et le y: " << sommetId.y << endl;
        cout << " Type terrain: " << sommet.typeTerrain << endl;
        cout << " Ses voisins orthogonal: ";
        for (const S& voisin : sommet.voisinsOrthogonal) {
            cout << "(" << voisin.x << ", " << voisin.y << ") ";
        }
        cout << endl;
        cout << " Ses voisins diagonal: ";
        for (const S& voisin : sommet.voisinsDiagonal) {
            cout << "(" << voisin.x << ", " << voisin.y << ") ";
        }
        cout << endl;
        cout << "  Cout départ (orthogonal): " << sommet.coutDepartOrthogonal << endl;
        cout << "  Cout départ (diagonal): " << sommet.coutDepartDiagonal << endl;
        cout << "  Cout arrivée (orthogonal): " << sommet.coutArriveOrthogonal << endl;
        cout << "  Cout arrivée (diagonal): " << sommet.coutArriveDiagonal << endl;
        cout << endl;
    }
}

#endif