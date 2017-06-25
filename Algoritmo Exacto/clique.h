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
	clique(const clique &c);
	bool puede_agregarse(unsigned int nodo);
	void agregar_nodo(unsigned int nodo,vector<int> vecinos);
	unsigned int size();
	bool empty();
	vector<int> vertices();
	unsigned int frontera();
	void mostrar();
	unsigned int maximo_afuera();
	unsigned int cantidad_candidatos();

	private:
	set<int> nodos;
	unsigned int tamfrontera;
	set<int> vecindad;
};
#endif