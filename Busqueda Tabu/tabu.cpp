#include <queue>
#include <limits>
#include "tabu.h"
enum operacion { AGREGAR, ELIMINAR, INTERCAMBIAR };

bool sonAdyacentes(const vector<int> i,int indiceI, const vector<int> j, int indiceJ){
    return find(i.begin(),i.end(),indiceJ) != i.end() && find(j.begin(),j.end(),indiceI) != j.end();
}

bool puede_agregarse(const vector<int> &clique, int nodo) {
    return !(find(clique.begin(), clique.end(), nodo) != clique.end());
}

bool sigueSiendoCliqueSiAgrego(const vector<vector<int> > &grafo,
                                const vector<int> &clique,
                                int nodo){
    for(int i = 0; i < clique.size(); ++i) {
    if(!sonAdyacentes(grafo[clique[i]],clique[i], grafo[nodo],nodo)) return false;
        }
    return true;
}

bool intercambiandoSigueSiendoClique(const vector<vector<int> > &grafo,
                                     const vector<int> &clique,
                                     int nodoViejo,
                                     int nodoNuevo) {
    for (size_t i = 0; i < clique.size(); ++i) {
        if(i != (size_t) nodoViejo &&
           !sonAdyacentes(grafo[clique[i]],clique[i], grafo[nodoNuevo],nodoNuevo)) return false;
    }
    return true;
}


size_t cantidad_tabu() {
    return cola.size();
}

void nodos_tabu(size_t tam){
    tam = tam;
 }

void marcar(int nodo) {
    conjunto.insert(nodo);
    cola.push(nodo);

    // Si me excedo del tamaño máximo, quito el elemento más viejo.
    if(cola.size() > tam) {
        conjunto.erase(cola.front());
        cola.pop();
    }
}

bool es_tabu(int nodo) {
    return conjunto.find(nodo) != conjunto.end();
}

pair<int,vector<int>> tabu(const vector<vector<int> > &grafo, 
                const pair<int,vector<int> > &clique,
                unsigned movimientosTabu,
                unsigned cantidadDeNodosTabu){
    pair<int,vector<int> > mejorSolucion = make_pair(0,vector<int>());
    tam = cantidadDeNodosTabu;
    bool faseTabu = false;
    unsigned movimientosTabuRestantes = movimientosTabu;
    while(true) {
        operacion op = ELIMINAR;
        int nodoAAgregar;
        int nodoAEliminar;
        pair<int, int> nodosAIntercambiar;
        int aporte = numeric_limits<int>::min();
        for(unsigned i = 0; i < grafo.size(); ++i) {
            if(es_tabu(i)) continue;
            if(puede_agregarse(clique.second,i) &&
                sigueSiendoCliqueSiAgrego(grafo,solucion.second,i)){  
                int aporteAgregar = grafo[i].size() - 2*solucion.second.size();
                if(aporteAgregar > aporte) {
                    op = AGREGAR;
                    nodoAAgregar = i;
                    aporte = aporteAgregar;
                }
            }
        }
        for(unsigned i = 0; i < solucion.second.size();++i){
            if(es_tabu(i)) continue;
            int iEsimo = solucion.second[i];
            int aporteIEsimo = grafo[iEsimo].size() -
                               (solucion.second.size() - 1);
            for (unsigned j = 0; j < grafo.size(); ++j) {
                if(es_tabu(j)) continue;
                if(puede_agregarse(solucion.second,j) &&
                    intercambiandoSigueSiendoClique(grafo,clique,i,j)){
                    int aporteJEsimo = nodos[j].size() -
                                       (solucion.second.size() - 1);
                    int aporteNeto = aporteJEsimo - aporteIEsimo;
                    if(aporteNeto > aporte) {
                        aporte = aporteNeto;
                        op = INTERCAMBIAR;
                        nodosAIntercambiar = make_pair(i, j);
                    }
                }
            }
        }
        for(unsigned i = 0; i < solucion.second.size(); ++i) {
            if(es_tabu(solucion.second[i])) continue;
            int iEsimo = solucion.second[i];
            int aporteEliminar = 2 * (solucion.second.size() - 1) -
                                 grafo[iEsimo].size();
            if(aporteEliminar > aporte) {
                op = ELIMINAR;
                nodoAEliminar = i;
                aporte = aporteEliminar;
            }
        }
        if(aporte <= 0) {
            if(!faseTabu) {
                mejorSolucion = solucion;
                faseTabu = true;
            }
            if(cantidad_tabu() == grafo.size()) return mejorSolucion;
            bool solucionTabu = true;
            for (unsigned i = 0; i < solucion.second.size(); ++i) {
                if(!es_tabu(solucion.second[i])) solucionTabu = false;
            }
            if(op == ELIMINAR && solucionTabu) return mejorSolucion;
            switch(op) {
                case AGREGAR:      marcar(nodoAAgregar); break;
                case ELIMINAR:     marcar(nodoAEliminar); break;
                case INTERCAMBIAR: marcar(nodosAIntercambiar.first);
            }
            movimientosTabuRestantes--;
            if(movimientosTabuRestantes == 0) return mejorSolucion;
        }
        else if(faseTabu && (aporte + solucion.first > mejorSolucion.first)) {
            faseTabu = false;
            movimientosTabuRestantes = movimientosTabu;
        }
        switch(op) {
            case AGREGAR:
            solucion.second.push_back(nodoAAgregar);
            break;

            case ELIMINAR:
            solucion.second.erase(
                    solucion.second.begin() + nodoAEliminar);
            break;

            case INTERCAMBIAR:
            solucion.second[nodosAIntercambiar.first] =
                    nodosAIntercambiar.second;
        }

        solucion.first += aporte;
    }
}    
