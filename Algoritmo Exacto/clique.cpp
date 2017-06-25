#include "clique.h"

clique::clique(){
	tamfrontera=0;
}

clique::clique(const clique &c){
	tamfrontera=c.tamfrontera;
	nodos=c.nodos;
	vecindad=c.vecindad;
}

bool clique::puede_agregarse(unsigned int nodo){
	if(nodos.empty())
		return true;
	return find (vecindad.begin(), vecindad.end(),nodo) != vecindad.end();
}

unsigned int clique::cantidad_candidatos(){
	return vecindad.size();
}

void clique::agregar_nodo(unsigned int nodo,vector<int> vecinos){
	if(nodos.empty()){
		for(vector<int>::iterator it=vecinos.begin();it!=vecinos.end();it++){
			vecindad.insert(*it);
		}
		tamfrontera=vecinos.size();
	}
	else{
		set<int> interseccion;
		for(set<int>::iterator it=vecindad.begin();it!=vecindad.end();it++){
			if(find (vecinos.begin(), vecinos.end(),*it) != vecinos.end())
				interseccion.insert(*it);
		}
		vecindad=interseccion;
		tamfrontera=tamfrontera+vecinos.size()-2*nodos.size();
	}
	nodos.insert(nodo);
}

unsigned int clique::size(){
	return nodos.size();
}
bool clique::empty(){
	return nodos.empty();
}

vector<int> clique::vertices(){
	vector<int> res;
	for(set<int>::iterator it=nodos.begin();it!=nodos.end();it++){
		res.push_back(*it);
	}
	return res;
}

unsigned int clique::frontera(){
	return tamfrontera;
}

void clique::mostrar(){
	cout<<"nodos: "<<nodos.size()<<" frontera: "<<tamfrontera<<endl;
	for(set<int>::iterator it=vecindad.begin();it!=nodos.end();it++){
		cout<<*it<<" ";
	}
	cout<<endl;
}
