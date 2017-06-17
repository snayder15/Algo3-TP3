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
		vector<int> CMF();
		void mostrar_grafo();

	private:
		vector<int>  interseccion_vecinos(vector<int> a,vector<int> b);
		unsigned int auxiliar_buscar_CMF(unsigned int nodos_agregados,unsigned int parcial,vector<int> &sol_parcial, vector<int> candidatos);
		clique aux(unsigned int i,clique c,unsigned int anadidos);
		grafo grafo_original;
		int maxima_clique_posible;
		vector<int> solucion;
		unsigned int max_CMF;
};
#endif