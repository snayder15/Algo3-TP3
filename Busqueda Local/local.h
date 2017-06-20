#ifndef LOCAL_H
#define LOCAL_H
#include <vector>
#include <utility>
using namespace std;

pair<int,vector<int>> local(const vector<vector<int> > &grafo, const pair<int, vector<int> > &clique);
bool puede_agregarse(const vector<int> &clique, int nodo);
bool sonAdyacentes(const vector<int> i,int indiceI, const vector<int> j, int indiceJ);
bool sigueSiendoCliqueSiAgrego(const vector<vector<int> > &grafo,
                                const vector<int> &clique,
                                int nodo);
bool intercambiandoSigueSiendoClique(const vector<vector<int> > &grafo,
                                     const vector<int> &clique,
                                     int nodoViejo,
                                     int nodoNuevo);
#endif 
