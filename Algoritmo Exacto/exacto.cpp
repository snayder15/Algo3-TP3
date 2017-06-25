#include "exacto.h"
exacto::exacto(){

}

clique exacto::aux(unsigned int i,clique c){
	if(i>=grafo_original.vertices())
		return c;
	if(2*c.size()>(grafo_original.vertices()))
		return c;
	clique res_agregado;
	if(c.puede_agregarse(i)){
		clique agregando=c;
		agregando.agregar_nodo(i,grafo_original.adyacentes(i));
		if(c.empty()||(c.frontera()<agregando.frontera())){
			res_agregado=aux(i+1,agregando);
		}
		else{
			res_agregado=c;
		}
	}
	clique res_sin_agregar=aux(i+1,c);
	if(res_agregado.frontera()>=res_sin_agregar.frontera()){
		return res_agregado;
	}
	return res_sin_agregar;
}

unsigned int exacto::buscar_CMF(grafo g){
	max_CMF=0;
	grafo_original=g;
	clique inicial;
	solucion=aux(0,inicial);
	return solucion.frontera();
}

void exacto::mostrar_grafo(){
	grafo_original.mostrar_grafo();
}

vector<int> exacto::nodos_CMF(){
	return solucion.vertices();
}