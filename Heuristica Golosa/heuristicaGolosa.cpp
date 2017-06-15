#include "heuristicaGolosa.h"

heuristicaGolosa::heuristicaGolosa(){
}

void heuristicaGolosa::init(int vertices,int aristas){
	cant_vertices=vertices;
	cant_aristas=aristas;	
	grafo.resize(vertices);
}

void heuristicaGolosa::cargar_ejes(int v1,int v2){
		grafo[v1-1].push_back (v2-1);
		grafo[v2-1].push_back (v1-1);
}

void heuristicaGolosa::clique_maxima(){
	int vertice_actual = mayor_grado();
	clique.first = grafo[vertice_actual].size();
	clique.second.push_back(vertice_actual);
	bool encontre_clique_max = false;
	while(!encontre_clique_max){
		int frontera_maxima = 0;
		int candidato = -1;
		for(unsigned int i = 0; i < grafo[vertice_actual].size(); i++){
			int vertice_vecino = grafo[vertice_actual][i];
			int frontera_vecino = 0;
			if(!pertenece_a_la_clique(vertice_vecino) && entra_en_la_clique(vertice_vecino)){
				frontera_vecino = grafo[vertice_vecino].size() + clique.first - (2 * clique.second.size());
			} 
			if(frontera_vecino > frontera_maxima){
				frontera_maxima = frontera_vecino;
				candidato = vertice_vecino;
			}
		}
		if(clique.first > frontera_maxima){
			encontre_clique_max = true;
		}else{
			vertice_actual = candidato;
			clique.second.push_back(candidato);
			clique.first = frontera_maxima;
		}
	} 
}

int heuristicaGolosa::mayor_grado(){
	int mayor = 0;
	for (unsigned int i = 1; i < grafo.size(); i++){
		if(grafo[i].size() > grafo[mayor].size()){
			mayor = i;
		}
	}
	return mayor;
}

bool heuristicaGolosa::pertenece_a_la_clique(int v){
	for(unsigned int i = 0; i < clique.second.size(); i++){
		if(v == clique.second[i]){
			return true;
		}
	}
	return false;
}

bool heuristicaGolosa::entra_en_la_clique(int v){
	for(unsigned int i = 0; i < clique.second.size(); i++){
			if(!son_adyacentes(clique.second[i],v)){
				return false;
			}
	}
	return true;
}

bool heuristicaGolosa::son_adyacentes(int v1,int v2){
	for(unsigned int i = 0; i < grafo[v2].size(); i++){
		if(v1 == grafo[v2][i] ){
			return true;
		}
	}

	return false;
}

void heuristicaGolosa::mostrar_solucion(){
	unsigned int k = clique.second.size();
	unsigned int frontera = clique.first;
	cout << frontera << " ";
	cout << k << "";
	for (unsigned int i = 0; i<k; i++){
		cout << " " << clique.second[i] + 1 << "";
	}
}