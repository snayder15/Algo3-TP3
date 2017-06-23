#include "exacto.h"
exacto::exacto(){

}
vector<int>  exacto::interseccion_vecinos(vector<int> a,vector<int> b){
	//O(E^2)
	vector<int> resultado;
	if(a.size()>b.size()){
		a.swap(b);
	}
	for (unsigned int i=0;i<a.size();i++){
 		std::vector<int>::iterator it = find (b.begin(), b.end(), a[i]);
 		if (it != b.end()){
 			resultado.push_back(a[i]);
 		}
	}
	return resultado; 
}

unsigned int exacto::auxiliar_buscar_CMF(unsigned int nodos_agregados,unsigned int parcial,vector<int> &sol_parcial, vector<int> candidatos){
	if(grafo_original.vertices()/2<nodos_agregados){
		//la clique encontrada no agrega nada util
		return parcial;
	}
	for(unsigned int i=0;i<candidatos.size();i++){
		vector<int> vecinos=grafo_original.adyacentes(candidatos[i]);
		if(vecinos.size()-nodos_agregados>0){
			vector<int> vecindad_valida=interseccion_vecinos(vecinos,candidatos);
			sol_parcial.push_back(candidatos[i]);
	 		unsigned int res_parcial=auxiliar_buscar_CMF(nodos_agregados+1,parcial,sol_parcial,vecindad_valida);
			res_parcial=res_parcial+vecinos.size()-sol_parcial.size();
			if(res_parcial>parcial){
				parcial=res_parcial;
			}
			else{
				std::vector<int>::iterator it = find (sol_parcial.begin(), sol_parcial.end(),candidatos[i]);
	 			sol_parcial.erase(it);

			}
		}
	}
	return parcial;
}
/*
unsigned int exacto::buscar_CMF(grafo g){
	max_CMF=0;
	grafo_original=g;
	if(g.vertices()>0){
		solucion.push_back(0);//como minimo el CMF es el nodo con mas aristas incidentes
		vector<int> vecinos=g.adyacentes(0);
		max_CMF=vecinos.size();
	}
	vector<vector<clique > > cliques;
	//analizo las soluciones de forma recursiva
	for(unsigned int i=0;i<g.vertices();i++){
		//elijo un pivot distinto para cada caso(evita problemas con no conexo)
		vector<int> solucion_inicial(1,i);
		vector<int> candidatos=g.adyacentes(i);
		unsigned int res_parcial=auxiliar_buscar_CMF(1,candidatos.size(),solucion_inicial,candidatos);
		if(res_parcial>max_CMF){
			max_CMF= res_parcial;
			solucion=solucion_inicial;
		}
	}
	return max_CMF;
}
*/


clique exacto::aux(unsigned int i,clique c,unsigned int anadidos){
	//cout<<"agregando nodo "<<i<<endl;
	if(i>=grafo_original.vertices())
		return c;
	if(anadidos>(grafo_original.vertices()/2))
		return c;
	if(c.cantidad_candidatos()==0)
		return c;
	clique agregando=c;
	clique res_agregado=c;
	if(agregando.puede_agregarse(i)){
		agregando.agregar_nodo(i,grafo_original.adyacentes(i));
		res_agregado=aux(i+1,agregando,anadidos+1);
	}
	clique res_sin_agregar=aux(i+1,c,anadidos);
	if(res_agregado.frontera()>res_sin_agregar.frontera()){
		return res_agregado;
	}
	return res_sin_agregar;
}

unsigned int exacto::buscar_CMF(grafo g){
	max_CMF=0;
	grafo_original=g;
	clique inicial;
	clique res=aux(0,inicial,0);
	solucion=res.vertices();
	return res.frontera();
}



void exacto::mostrar_grafo(){
	grafo_original.mostrar_grafo();
}

vector<int> exacto::CMF(){
	vector<int> adaptado;
	for(unsigned int i=0;i<solucion.size();i++){
		adaptado.push_back(solucion[i]+1);
	}
	return adaptado;
}