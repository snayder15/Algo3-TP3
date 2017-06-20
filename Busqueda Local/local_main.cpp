#include <iostream>

#include "local.h"
#include "../Heuristica Golosa/heuristicaGolosa.h"

using namespace std;


int main() {
    unsigned n;
    unsigned m;
    heuristicaGolosa golosa;
    cin >> n;
    //if(cin.eof()) break;
    cin >> m;
    //if(cin.eof()) break;
    //string s;
    //getline(cin, s);
    golosa.init(n,m);
    for(unsigned i = 0; i < m; ++i) {
        unsigned v, w;
        cin >> v;
        cin >> w; 
        golosa.cargar_ejes(v,w);
        //getline(cin, s);
    }
    golosa.clique_maxima();
    vector<vector<int> > graph;
    graph = golosa.graph();
    pair<int, vector<int> > cliqueGolosa = golosa.clique_golosa();
    pair<int, vector<int> > cliqueLocal = local(graph, cliqueGolosa);
    cout << cliqueLocal.first << " " << cliqueLocal.second.size() << " ";
    for (unsigned i = 0; i < cliqueLocal.second.size(); ++i) {
        cout << cliqueLocal.second[i]+1;
        if(i + 1 < cliqueLocal.second.size()) cout << " ";
    }
    cout << endl;
    return 0;
}