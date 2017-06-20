#ifndef TABU_H
#define TABU_H

using namespace std;

set<indice_nodo> conjunto;
queue<indice_nodo> cola;
size_t tam;
nodos_tabu(size_t tam);
void marcar(indice_nodo nodo);
bool es_tabu(indice_nodo nodo);
size_t cantidad_tabu();
pair<int,vector<int>> tabu(const vector<vector<int> > &grafo, 
				const pair<int,vector<int> > &clique,
				unsigned movimientosTabu,
		 		unsigned cantidadDeNodosTabu);

#endif // TABU_H