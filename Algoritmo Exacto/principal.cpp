#include <chrono>
#include <stdlib.h>
#include <utility>
#include <iostream>

#define ya chrono::high_resolution_clock::now
#include "grafos.h"
#include "exacto.h"

using namespace std;

int main(int argc,char * argv[]){
	int cant_nodos,cant_aristas,nodo_a,nodo_b;
	//cout<<"ingresar numero de nodos"<<endl;
	cin>>cant_nodos;
	//cout<<"ingresar numero de aristas"<<endl;
	cin>>cant_aristas;
	grafo g;
	g.init(cant_nodos);
	for(int i=0;i<cant_aristas;i++){
		cin>>nodo_a;
		cin>>nodo_b;
		g.anadir_ejes_rapido(nodo_a,nodo_b);
	}
	exacto instancia;
	auto start = ya();
	int resultado=instancia.buscar_CMF(g);
	auto end = ya();
	vector<int> solucion=instancia.CMF();
	if(argc>1){
		cerr<<"escribiendo tiempos"<<endl;
		cout<<cant_nodos<<";"<<cant_aristas<<";"<<resultado<<";"<<solucion.size()<<";";
		cout << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count()<<endl;
	}
	else{
		cout<<resultado<<" "<<solucion.size();
		for(unsigned int i=0;i<solucion.size();i++){
			cout<<" "<<solucion[i];
		}
		cout<<endl;
	}
	
	
	return 0;
}