#include "local.h"

using namespace std;

enum operacion { AGREGAR, ELIMINAR, INTERCAMBIAR };


bool puede_agregarse(const vector<int> &clique, int vertice) {
    return !(find(clique.begin(), clique.end(), vertice) != clique.end());
}

bool sonAdyacentes(const vector<int> i,int indiceI, const vector<int> j, int indiceJ){
    return find(i.begin(),i.end(),indiceJ) != i.end() && find(j.begin(),j.end(),indiceI) != j.end();
}

bool sigueSiendoCliqueSiAgrego(const vector<vector<int> > &grafo,
                                const vector<int> &clique,
                                int vertice){
    for(int i = 0; i < clique.size(); ++i) {
    if(!sonAdyacentes(grafo[clique[i]],clique[i], grafo[vertice],vertice)) return false;
        }
    return true;
}

bool intercambiandoSigueSiendoClique(const vector<vector<int> > &grafo,
                                     const vector<int> &clique,
                                     int verticeViejo,
                                     int verticeNuevo) {
    for (size_t i = 0; i < clique.size(); ++i) {
        if(i != (size_t) verticeViejo &&
           !sonAdyacentes(grafo[clique[i]],clique[i], grafo[verticeNuevo],verticeNuevo)) return false;
    }
    return true;
}

pair<int,vector<int>> local(const vector<vector<int> > &grafo, const pair<int, vector<int> > &clique){
    pair<int,vector<int>> solucion = clique;
    while(true) {
        operacion operacion;
        int verticeAAgregar;
        int verticeAEliminar;
        pair<int, int> verticesAIntercambiar;
        int cantAporte = 0; 
        // agregar
        for(unsigned i = 0; i < grafo.size(); ++i) {
            if(puede_agregarse(solucion.second,i) && 
                sigueSiendoCliqueSiAgrego(grafo,solucion.second, i)){
                int aporteAgregar = grafo[i].size() -
                                   2 * solucion.second.size();
                if(aporteAgregar > cantAporte) {
                    operacion = AGREGAR;
                    verticeAAgregar = i;
                    cantAporte = aporteAgregar;
                }
            }
        }
        // intercambiar
        for(unsigned i = 0; i < solucion.second.size(); ++i) {
            int iEsimo = solucion.second[i];
            int aporteIEsimo = grafo[iEsimo].size() - ( solucion.second.size() - 1);
            for (unsigned j = 0; j < grafo.size(); ++j) {
                if(puede_agregarse(solucion.second,j) &&
                    intercambiandoSigueSiendoClique(grafo,solucion.second,i,j)){ 
                    int aporteJEsimo = grafo[j].size() -
                                       (solucion.second.size() - 1);
                    int aporteNeto = aporteJEsimo - aporteIEsimo;
                    if(aporteNeto > cantAporte) {
                        cantAporte = aporteNeto;
                        operacion = INTERCAMBIAR;
                        verticesAIntercambiar = make_pair(i, j);
                    }
                }
            }
        }
        // eliminar
        for(unsigned i = 0; i < solucion.second.size(); ++i) {
            int iEsimo = solucion.second[i];
            int aporteEliminar = 2 * (solucion.second.size() - 1) -
                                 grafo[iEsimo].size();
            if(aporteEliminar > cantAporte) {
                operacion = ELIMINAR;
                verticeAEliminar = i;
                cantAporte = aporteEliminar;
            }
        }
        if(cantAporte == 0) break;
        switch(operacion) {
            case AGREGAR:
            solucion.second.push_back(verticeAAgregar);
            break;
            case ELIMINAR:
            solucion.second.erase(
                    solucion.second.begin() + verticeAEliminar);
            break;
            case INTERCAMBIAR:
            solucion.second[verticesAIntercambiar.first] =
                    verticesAIntercambiar.second;
        }
        solucion.first += cantAporte;
    }
    return solucion;

}
