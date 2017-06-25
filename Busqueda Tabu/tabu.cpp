#include <queue>
#include <limits>
#include "tabu.h"
enum operacion { AGREGAR, ELIMINAR, INTERCAMBIAR };

set<int> conjunto;
queue<int> cola;
size_t tam;

bool sonAdyacentes(const vector<int> i,int indiceI, const vector<int> j, int indiceJ){
    return find(i.begin(),i.end(),indiceJ) != i.end() && find(j.begin(),j.end(),indiceI) != j.end();
}

bool puede_agregarse(const vector<int> &clique, int vertice) {
    return !(find(clique.begin(), clique.end(), vertice) != clique.end());
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


size_t cantTabu() {
    return cola.size();
}

void verticesTabu(size_t tam){
    tam = tam;
 }

void marcar(int vertice) {
    conjunto.insert(vertice);
    cola.push(vertice);

    // Si me excedo del tamaño máximo, quito el elemento más viejo.
    if(cola.size() > tam) {
        conjunto.erase(cola.front());
        cola.pop();
    }
}

bool esTabu(int vertice) {
    return conjunto.find(vertice) != conjunto.end();
}

pair<int,vector<int>> tabu(const vector<vector<int> > &grafo, 
                const pair<int,vector<int> > &clique,
                unsigned movimientosTabu,
                unsigned cantidadDeverticesTabu){
    pair<int,vector<int>> solucion = clique; 
    pair<int,vector<int> > mejorSolucion = make_pair(0,vector<int>());
    tam = cantidadDeverticesTabu;
    bool faseTabu = false;
    unsigned movimientosTabuRestantes = movimientosTabu;
    while(true) {
        operacion op = ELIMINAR;
        int verticeAAgregar;
        int verticeAEliminar;
        pair<int, int> verticesAIntercambiar;
        int aporte = numeric_limits<int>::min();
        for(unsigned i = 0; i < grafo.size(); ++i) {
            if(esTabu(i)) continue;
            if(puede_agregarse(clique.second,i) &&
                sigueSiendoCliqueSiAgrego(grafo,solucion.second,i)){  
                int aporteAgregar = grafo[i].size() - 2*solucion.second.size();
                if(aporteAgregar > aporte) {
                    op = AGREGAR;
                    verticeAAgregar = i;
                    aporte = aporteAgregar;
                }
            }
        }
        for(unsigned i = 0; i < solucion.second.size();++i){
            if(esTabu(i)) continue;
            int iEsimo = solucion.second[i];
            int aporteIEsimo = grafo[iEsimo].size() -
                               (solucion.second.size() - 1);
            for (unsigned j = 0; j < grafo.size(); ++j) {
                if(esTabu(j)) continue;
                if(puede_agregarse(solucion.second,j) && 
                    intercambiandoSigueSiendoClique(grafo,solucion.second,i,j)){
                    int aporteJEsimo = grafo[j].size() -
                                       (solucion.second.size() - 1);
                    int aporteNeto = aporteJEsimo - aporteIEsimo;
                    if(aporteNeto > aporte) {
                        aporte = aporteNeto;
                        op = INTERCAMBIAR;
                        verticesAIntercambiar = make_pair(i, j);
                    }
                }
            }
        }
        for(unsigned i = 0; i < solucion.second.size(); ++i) {
            if(esTabu(solucion.second[i])) continue;
            int iEsimo = solucion.second[i];
            int aporteEliminar = 2 * (solucion.second.size() - 1) -
                                 grafo[iEsimo].size();
            if(aporteEliminar > aporte) {
                op = ELIMINAR;
                verticeAEliminar = i;
                aporte = aporteEliminar;
            }
        }
        if(aporte <= 0) {
            if(!faseTabu) {
                mejorSolucion = solucion;
                faseTabu = true;
            }
            if(cantTabu() == grafo.size()) return mejorSolucion;
            bool solucionTabu = true;
            for (unsigned i = 0; i < solucion.second.size(); ++i) {
                if(!esTabu(solucion.second[i])) solucionTabu = false;
            }
            if(op == ELIMINAR && solucionTabu) return mejorSolucion;
            switch(op) {
                case AGREGAR:      marcar(verticeAAgregar); break;
                case ELIMINAR:     marcar(verticeAEliminar); break;
                case INTERCAMBIAR: marcar(verticesAIntercambiar.first);
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

        solucion.first += aporte;
    }
}    
