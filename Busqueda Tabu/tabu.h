#ifndef TABU_H
#define TABU_H

#include <set>
#include <queue>
#include <limits>
#include <vector>
#include <utility>
#include <algorithm> 

using namespace std;

set<int> conjunto;
queue<int> cola;
size_t tam;
void nodos_tabu(size_t tam);
void marcar(int nodo);
bool es_tabu(int nodo);
size_t cantidad_tabu();
pair<int,vector<int>> tabu(const vector<vector<int> > &grafo, 
				const pair<int,vector<int> > &clique,
				unsigned movimientosTabu,
		 		unsigned cantidadDeNodosTabu);

#endif // TABU_H