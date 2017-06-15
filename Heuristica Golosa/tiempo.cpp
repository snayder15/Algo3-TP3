#include <iostream>
#include "heuristicaGolosa.h"

#include <chrono>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <iostream>
#include <climits>
#define ya chrono::high_resolution_clock::now

using namespace std;

int main(int argc,char * argv[]){
	int cant_vertice,cant_arista;
	heuristicaGolosa instancia;
	int v1,v2;
	cin>>cant_vertice;
	cin>>cant_arista;
	cin>>v1;
	cin>>v2;
	instancia.init(cant_vertice,cant_arista);
	for(int i=0;i<cant_arista;i++){
		cin>>v1;
		cin>>v2;
		instancia.cargar_ejes(v1,v2);
	}
	cerr<<"Iniciando medicion de tiempo"<<endl;
	auto start = ya();
	instancia.clique_maxima();
	auto end = ya();
	cout<<cant_vertice<<";";
	cout << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << ";"<<endl;
	
	return 0;
}