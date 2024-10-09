#include "graph.h"
using namespace std;

Graph::Graph(): num_vertices(0) {}

// u = nodo di partenza, v = nodo di arrivo, w = peso
void Graph::addEdge(int u, int v, int w) {

    edges.push_back({u, v, w});
    /* serve per tenere conto di tutti i vertici presenti; se u+1 o v-1 sono maggiori di num_vertices,
    significa che u o v sono magigori di qualsiasi altro indice già presente ed è necessario incrementare
    il numero di vertici*/
    if (u + 1 > num_vertices) num_vertices = u + 1;
    if (v + 1 > num_vertices) num_vertices = v + 1;
}

//cancella il grafo per salvarne uno nuovo
void Graph::clear() {

    edges.clear();
    num_vertices = 0;
}

//stampa il grafo salvato da file
void Graph::print() const {

    for (const auto& edge : edges) {

        cout << "Node " << edge.u << " <-> Node " << edge.v << " weight " << edge.w << endl;
    }
}

//ritorna il numero di vertici
int Graph::numVertices() const {
    return this->num_vertices;
}

//ritorna il numero di archi
const std::vector<Graph::Edge>& Graph::getEdges() const {
	return edges;
}