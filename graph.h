#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>

class Graph {

    public:
        // struct per salvare i dati di un arco generico con nodo di partenza, nodo di arrivo e peso
        struct Edge {
            int u, v, w;
        };

        Graph(); //default constructor
        void addEdge(int u, int v, int w);
        void clear();
        void print() const;
        int numVertices() const;
        const std::vector<Edge>& getEdges() const;

    private:
        //vettore di archi
        std::vector<Edge> edges;
        //intero per memorizzare il numero di vertici
        int num_vertices;
};

#endif