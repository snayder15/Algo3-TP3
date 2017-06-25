#ifndef TABU_H
#define TABU_H

#include <set>
#include <queue>
#include <limits>
#include <vector>
#include <utility>
#include <algorithm> 

using namespace std;

void verticesTabu(size_t tam);
void marcar(int vertice);
bool esTabu(int vertice);
size_t cantTabu();
pair<int,vector<int>> tabu(const vector<vector<int> > &grafo, 
				const pair<int,vector<int> > &clique,
				unsigned movimientosTabu,
		 		unsigned cantidadDeverticesTabu);

#endif // TABU_H