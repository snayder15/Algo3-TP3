#ifndef dijstra_h
#define dijstra_h

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class heuristicaGolosa{
	public:
		heuristicaGolosa();
		void init(int vertices,int aristas);
		void cargar_ejes(int v1,int v2);
		int mayor_grado();
		void clique_maxima();
		bool entra_en_la_clique(int v);
		bool pertenece_a_la_clique(int v);
		bool son_adyacentes(int v1,int v2);
		void mostrar_solucion();
	private:
		vector<vector<int> > grafo;
		pair<int,vector<int> > clique;
		int cant_vertices;
		int cant_aristas;
		
};
#endif