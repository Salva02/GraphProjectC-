#include "problemSolver.h"
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>
#include <algorithm>
using namespace std;

// u è il nodo di cui si vuole trovare l'insieme rappresentante, il vettore parent memorizza il genitore di ogni nodo
int MSTSolver::find(int u, vector<int>& parent) {
	// controlla se il nodo u è rappresentante del proprio insieme
	if(u != parent[u]) {
		// chiamata ricorsiva fino a che non si trova il rappresentante dell'insieme di u
		parent[u] = find(parent[u], parent);
	}

	return parent[u];
}

// u e v sono i nodi da unire
void MSTSolver::unionSets(int u, int v, vector<int>& parent, vector<int>& rank) {
	// si trovano le radici dei nodi
	int rootU = find(u, parent);
	int rootV = find(v, parent);

	// rappresentanti diversi, nodi in insiemi diversi che devono essere uniti
	if(rootU != rootV) {
		if(rank[rootU] > rank[rootV]) {
			parent[rootV] = rootU;
		} else if(rank[rootU] < rank[rootV]) {
			parent[rootU] = rootV;
		} else {
			parent[rootV] = rootU;
            // ho unito due alberi di pari rango quindi bisogna aumentare l'altezza 
			rank[rootU]++;
		}
	}
}

ProblemSolution* MSTSolver::solve(const Graph& graph) {
    // creazione di un vettore di archi
    vector<Graph::Edge> edges = graph.getEdges();
    // ordinamento crescente degli archi senza cicli
    sort(edges.begin(), edges.end(), [](const Graph::Edge& a, const Graph::Edge& b) {
        return a.w < b.w;
    });

    int totalWeight = 0;
    // archi dell'albero
    vector<Graph::Edge> mstEdges;
    // ogni nodo è il proprio genitore inizialmente
    vector<int> parent(graph.numVertices());
    // ranghi degli alberi inizializzati sempre a 0
    vector<int> rank(graph.numVertices(), 0);

    // inizializzazione di ogni nodo come proprio genitore
    for (int i = 0; i < graph.numVertices(); ++i) {
        parent[i] = i;
    }

    for (const auto& edge : edges) {
        int rootU = find(edge.u, parent);
        int rootV = find(edge.v, parent);

        if (edge.u >= parent.size() || edge.v >= parent.size()) {
        cerr << "Errore: edge.u o edge.v fuori dai limiti!" << endl;
        continue;
        }

        if (rootU != rootV) {
            unionSets(edge.u, edge.v, parent, rank);
            mstEdges.push_back(edge);
            totalWeight += edge.w;

        }
    }
    return new MST(mstEdges, totalWeight);
}

// costruttore con nodo di partenza e arrivo
SPSPSolver::SPSPSolver(int src, int dest) : source(src), destination(dest) {}

// overloaded funztion
ProblemSolution* SPSPSolver::solve(const Graph& graph) {
    return solve(graph, source, destination);
}


ProblemSolution* SPSPSolver::solve(const Graph& graph, int source, int destination) {
    // distanza minima da source a tutti gli altri nodi inizialmente infinita
    std::vector<int> distance(graph.numVertices(), std::numeric_limits<int>::max());
    // tiene traccia dei predecessori
    std::vector<int> previous(graph.numVertices(), -1);
    // coda di priorità per tenere conto della distanza minima corrente
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    distance[source] = 0;
    pq.push(std::make_pair(0, source));

    while (!pq.empty()) {
        // estrazione dalla coda del nodo con distanza minima 
        int u = pq.top().second;
        pq.pop();

        // iterazione di tutti gli archi
        for (const auto& edge : graph.getEdges()) {
            if (edge.u == u) {
            // per ogni arco che parte da u si cerca il nodo v e il peso dell'arco
            int v = edge.v;
            int weight = edge.w;

            // se la distanza da source a v passando per u è minore della distanza attualmente salvata
            if (distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    previous[v] = u;
                    // si inserisce v nella coda di priorità
                    pq.push(std::make_pair(distance[v], v));
                }
            }
        }
    }

    // costruzione del percorso più breve
    std::vector<int> shortestPath;
    int current = destination;
    // se il nodo destinzaione è raggiungibile
    if (distance[destination] != std::numeric_limits<int>::max()) {
        // si risale il cammino dal fondo
        while (current != -1) {
            shortestPath.push_back(current);
            current = previous[current];
        }
        // si inverte il cammino
        std::reverse(shortestPath.begin(), shortestPath.end());
    }

    return new ShortestPathSolution(shortestPath, distance[destination]);
}

// costruttore
SingleSourceSolver::SingleSourceSolver(int src) : source(src) {}

// overloaded function
ProblemSolution* SingleSourceSolver::solve(const Graph& graph) {
    return solve(graph, source);
}

ProblemSolution* SingleSourceSolver::solve(const Graph& graph, int source, int destination) {
    std::vector<int> distance(graph.numVertices(), std::numeric_limits<int>::max());
    std::vector<int> previous(graph.numVertices(), -1);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    distance[source] = 0;
    pq.push(std::make_pair(0, source));

    while (!pq.empty()) {
        // estrazione del nodo con distanza minima nella coda, è il prossimo nodo da esaminare
        int u = pq.top().second;
        pq.pop();

        for (const auto& edge : graph.getEdges()) {
            // per ogni arco che parte da u si analizzano i nodi v di arrivo e i pesi degli archi
            if (edge.u == u) {
                int v = edge.v;
                int weight = edge.w;

                // controlla se la distanza da source a v passando per u è minore della distanza attuale
                if (distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    previous[v] = u;
                    // si inserisce v nella coda insieme alla sua distanza
                    pq.push(std::make_pair(distance[v], v));
                }
            }
        }
    }

    return new SingleSourceSolution(distance, previous, source);
}


ProblemSolution* APSPSolver::solve(const Graph& graph) {
    // si ottiene numero di vertici e una matrice di dimensione V*V
    int V = graph.numVertices();
    std::vector<std::vector<int>> dist(V, std::vector<int>(V, std::numeric_limits<int>::max()));

    // la distanza da ogni nodo a sè stesso è messa a 0
    for (int i = 0; i < V; ++i) {
        dist[i][i] = 0;
    }

    // mette nella matrice i pesi e dei vari percorsi presenti nel grafo in esame
    for (const auto& edge : graph.getEdges()) {
        dist[edge.u][edge.v] = edge.w;
    }

    // per ogni coppia di nodi si controlla se esiste un percorso più breve utilizzando un nodo intermedio (k)
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                // nel caso il percorso esista si aggiorna il valore nella matrice
                if (dist[i][k] != std::numeric_limits<int>::max() && dist[k][j] != std::numeric_limits<int>::max()) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    return new APSPSolution(dist);
}
