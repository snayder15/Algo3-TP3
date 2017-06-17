#include "clique.h"

clique::clique(){
	tamfrontera=0;
}

bool clique::puede_agregarse(unsigned int nodo){
	if(nodos.empty())
		return true;
	return find (vecindad.begin(), vecindad.end(),nodo) != vecindad.end();
}

void clique::agregar_nodo(unsigned int nodo,vector<int> vecinos){
	if(nodos.empty()){
		for(vector<int>::iterator it=vecinos.begin();it!=vecinos.end();it++){
			vecindad.insert(*it);
		}
	}
	else{
		set<int> interseccion;
		for(set<int>::iterator it=vecindad.begin();it!=vecindad.end();it++){
			if(find (vecinos.begin(), vecinos.end(),*it) != vecinos.end())
				interseccion.insert(*it);
		}
		vecindad=interseccion;
		tamfrontera=tamfrontera+vecinos.size()-nodos.size();
	}
	nodos.insert(nodo);
}

unsigned int clique::size(){
	return nodos.size();
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
