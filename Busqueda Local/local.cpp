#include "local.h"

using namespace std;

enum operacion { AGREGAR, ELIMINAR, INTERCAMBIAR };


bool puede_agregarse(const vector<int> &clique, int nodo) {
    return !(find(clique.begin(), clique.end(), nodo) != clique.end());
}

bool sonAdyacentes(const vector<int> i,int indiceI, const vector<int> j, int indiceJ){
    return find(i.begin(),i.end(),indiceJ) != i.end() && find(j.begin(),j.end(),indiceI) != j.end();
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

pair<int,vector<int>> local(const vector<vector<int> > &grafo, const pair<int, vector<int> > &clique){
    pair<int,vector<int>> solucion = clique;
    while(true) {
       // Operación hallada (y parámetros) que más aumenta la frontera.
        operacion op;
        int nodoAAgregar;
        int nodoAEliminar;
        pair<int, int> nodosAIntercambiar;
        // Cantidad de aristas que aporta la operación.
        int aporte = 0; 
        // Operación AGREGAR.
        for(unsigned i = 0; i < grafo.size(); ++i) {
           // ¿Puedo agregar el nodo i-ésimo a la clique?
            if(puede_agregarse(solucion.second,i) && 
                sigueSiendoCliqueSiAgrego(grafo,solucion.second, i)){
                // Calculo cuántas aristas me aporta a la frontera.
                int aporteAgregar = grafo[i].size() -
                                   2 * solucion.second.size();

                // Decido si me quedo con la operación.
                if(aporteAgregar > aporte) {
                    op = AGREGAR;
                    nodoAAgregar = i;
                    aporte = aporteAgregar;
                }
            }
        }
        // Operación INTERCAMBIAR.
        for(unsigned i = 0; i < solucion.second.size(); ++i) {

            // Calculo cuántas aristas aporta el i-ésimo nodo de la clique.
            int iEsimo = solucion.second[i];
            int aporteIEsimo = grafo[iEsimo].size() - ( solucion.second.size() - 1);
            //int aporteIEsimo = nodos[iEsimo].adyacentes.size() -
            //                   (indices_nodos(solucion).size() - 1);

            // Consideramos el resto de los nodos del grafo.
            for (unsigned j = 0; j < grafo.size(); ++j) {

                // ¿Si lo intercambio por el i-ésimo, sigue siendo clique?
                if(puede_agregarse(solucion.second,j) &&
                    intercambiandoSigueSiendoClique(grafo,solucion.second,i,j)){ 
                //if(!estaEnLaClique(indices_nodos(solucion), j) &&
                //   intercambiandoSigueSiendoClique(
                //           nodos, indices_nodos(solucion), i, j)) {

                    // Calculo cuántas aristas aportaría el j-ésimo nodo
                    // del grafo.
                    int aporteJEsimo = grafo[j].size() -
                                       (solucion.second.size() - 1);

                    // Calculo el aporte neto de intercambiar ambos nodos.
                    int aporteNeto = aporteJEsimo - aporteIEsimo;

                    // Decido si me quedo con ésta operación.
                    if(aporteNeto > aporte) {
                        aporte = aporteNeto;
                        op = INTERCAMBIAR;
                        nodosAIntercambiar = make_pair(i, j);
                    }
                }
            }
        }

        // Operación ELIMINAR
        for(unsigned i = 0; i < solucion.second.size(); ++i) {

            // Calculo cuántas aristas agrega a la frontera el eliminar el
            // i-ésimo nodo de la clique.
            int iEsimo = solucion.second[i];
            int aporteEliminar = 2 * (solucion.second.size() - 1) -
                                 grafo[iEsimo].size();

            if(aporteEliminar > aporte) {
                op = ELIMINAR;
                nodoAEliminar = i;
                aporte = aporteEliminar;
            }
        }

        // Si alcanzamos un máximo local, terminamos.
        if(aporte == 0) break;

        // En caso contrario, realizo la operación que más aristas contribuye.
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

    return solucion;

}
