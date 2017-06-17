#ifndef grafos_h
#define grafos_h

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm> 

using namespace std;
#define distancia_infinita INT_MAX

class grafo{
	public:
		grafo();
		void init(int vertices);
		//inicializa el grafo con la cantidad de vertices y ejes indicados
		void anadir_ejes_rapido(int origen,int destino);
		//anade un eje al grafo
		//pre: origen y destino mayor igual a 0 y menor a cantidad de vertices
		//pre: el eje no fue anadido anteriormente
		void anadir_ejes(int origen,int destino);
		//anade un eje al grafo
		//pre: origen y destino mayor igual a 0 y menor a cantidad de vertices
		unsigned int vertices();
		//devuelve la cantidad de vertices del grafo
		vector<int> adyacentes(int vertice);
		//devuelve los nodos adyacentes a ese vertice
		void mostrar_grafo();
		//muestra la lista de adyacencias del grafo
	private:
		vector<vector<int> > lista_adyacencia;
		unsigned int nodos;
		unsigned int aristas;
};
#endif