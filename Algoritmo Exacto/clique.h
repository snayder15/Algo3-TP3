#ifndef clique_h
#define clique_h

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm> 
#include <set>
#include <climits>
using namespace std;

class clique{
	public:
	clique();
	bool puede_agregarse(unsigned int nodo);
	void agregar_nodo(unsigned int nodo,vector<int> vecinos);
	unsigned int size();
	vector<int> vertices();
	unsigned int frontera();
	void mostrar();
	unsigned int maximo_afuera();

	private:
	set<int> nodos;
	unsigned int tamfrontera;
	set<int> vecindad;
};
#endif