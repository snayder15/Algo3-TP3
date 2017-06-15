#include <iostream>
#include "heuristicaGolosa.h"

using namespace std;

int main(int argc,char * argv[]){
	vector<heuristicaGolosa> problema;
	int cant_vertice,cant_arista;
	cout << "ingresar el numero de vertices" << endl;
	cin >> cant_vertice;
	cout << "ingresar el numero de aristas" << endl;
	cin >> cant_arista;
	while(cant_vertice!=-1&&cant_arista!=-1){
		heuristicaGolosa instancia;
		instancia.init(cant_vertice,cant_arista);
		for(int i=0; i < cant_arista; i++){
			int v1,v2;
			cout << "ingresar vertice 1 vertice 2" << endl;
			cin >> v1;
			cin >> v2;
			instancia.cargar_ejes(v1,v2);
		}
		problema.push_back(instancia);
		cout << "ingresar el numero de vertices" << endl;
		cin >> cant_vertice;
		cout << "ingresar el numero de aristas" << endl;
		cin >> cant_arista;
	}

	for(unsigned int i=0;i<problema.size();i++){
		problema[i].clique_maxima();
		problema[i].mostrar_solucion();
	}

	
	return 0;
}