#ifndef exacto_h
#define exacto_h

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm> 
#include "grafos.h"
#include "clique.h"
using namespace std;

class exacto{
	public:
		exacto();
		unsigned int buscar_CMF(grafo g);
		vector<int> nodos_CMF();
		void mostrar_grafo();

	private:
		clique aux(unsigned int i,clique c);
		grafo grafo_original;
		int maxima_clique_posible;
		clique solucion;
		unsigned int max_CMF;
};
#endif