#include <iostream>

#include "tabu.h"
#include "../Heuristica Golosa/heuristicaGolosa.h"

using namespace std;


int main() {
    unsigned n;
    unsigned m;
    heuristicaGolosa golosa;
    cin >> n;
    cin >> m;
    golosa.init(n,m);
    for(unsigned i = 0; i < m; ++i) {
        unsigned v, w;
        cin >> v;
        cin >> w; 
        golosa.cargar_ejes(v,w);
    }
    golosa.clique_maxima();
    vector<vector<int> > graph;
    graph = golosa.graph();
    pair<int, vector<int> > cliqueGolosa = golosa.clique_golosa();
	pair<int, vector<int> > cliqueTabu = tabu(graph, cliqueGolosa, 3, 1);
	cout << cliqueTabu.first << " " << cliqueTabu.second.size() << " ";
	for (unsigned i = 0; i < cliqueTabu.second.size(); ++i) {
		cout << cliqueTabu.second[i]+1;
		if(i + 1 < cliqueTabu.second.size()) cout << " ";
	}
	cout << endl;
	return 0;
}