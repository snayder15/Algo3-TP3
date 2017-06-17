#include "grafos.h"

grafo::grafo(){

}

void grafo::init(int vertices){
	nodos=vertices;
	aristas=0;
	lista_adyacencia.resize(nodos);
}

void grafo::anadir_ejes_rapido(int origen,int destino){
	aristas++;
	lista_adyacencia[origen-1].push_back(destino-1);
	lista_adyacencia[destino-1].push_back(origen-1);
}

void grafo::anadir_ejes(int origen,int destino){
  	std::vector<int>::iterator it;
  	it = find (lista_adyacencia[origen].begin(), lista_adyacencia[origen].end(), destino);
  	if (it != lista_adyacencia[origen].end()){
		anadir_ejes_rapido(origen,destino);
  	}
}

unsigned int grafo::vertices(){
	return nodos;
}

vector<int> grafo::adyacentes(int vertice){
	return lista_adyacencia[vertice];
}
void grafo::mostrar_grafo(){
	cout<<"nodos: "<< nodos <<" aristas: "<<aristas<<endl;
	for(unsigned int i=0;i<nodos;i++){
		for(unsigned int j=0;j<lista_adyacencia[i].size();j++){
			cout<<"("<<i+1<<","<<lista_adyacencia[i][j]<<") ";
		}	
		cout<<endl;
	}
}

