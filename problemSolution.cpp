#include "problemSolution.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
using namespace std;

//costruttore
MST::MST(const vector<Graph::Edge>& edges, int weight): mstEdges(edges), totalWeight(weight) {}

std::ostream& MST::output(std::ostream& os) const {
    os << "Minimum Spanning Tree edges:\n";
    // itera il vettore contenente gli archi
    for (const auto& edge : mstEdges) {
        os << "Edge from " << edge.u << " to " << edge.v << " with weight " << edge.w << "\n";
    }
    os << "Total weight: " << totalWeight << "\n";
    return os;
}

void MST::exportSolution(const std::string& filename) const {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << "Minimum Spanning Tree edges: " << endl;
        for (const auto& edge : mstEdges) {
            outFile << "Edge from " << edge.u << " to " << edge.v << " with weight " << edge.w << endl;
        }
        outFile << "Total weight: " << totalWeight << endl;
        outFile.close();
    } else {
        cerr << "Unable to open file" << endl;
    }
}

// costruttore
ShortestPathSolution::ShortestPathSolution(const std::vector<int>& path, int distance) : shortestPath(path), shortestDistance(distance) {}

std::ostream& ShortestPathSolution::output(std::ostream& os) const {
    // controlla che il percorso esista
    if (shortestPath.empty()) {
        os << "No path available\n";
    } else {
        os << "Shortest Path: ";
        // itera il vettore contenente i nodi e per ognuno stampa l'elemento corrispondente
        for (size_t i = 0; i < shortestPath.size(); ++i) {
            os << shortestPath[i];
            // controlla che il nodo non sia l'ultimo del percorso
            if (i != shortestPath.size() - 1) {
                os << " -> ";
            }
        }
        // stampa la distanza
        os << "\nShortest path distance: " << shortestDistance << "\n";
    }
    return os;
}

void ShortestPathSolution::exportSolution(const std::string& filename) const {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << "Shortest path: ";
        for (int i = 0; i < shortestPath.size(); ++i) {
            outFile << shortestPath[i];
            if (i != shortestPath.size() - 1) {
                outFile << " -> ";
            }
        }
        outFile << "\nShortest path distance: " << shortestDistance << endl;
        outFile.close();
    } else {
        cerr << "Unable to open file" << endl;
    }
}

SingleSourceSolution::SingleSourceSolution(const std::vector<int>& dist, const std::vector<int>& prev, int src) : distances(dist), previous(prev), source(src) {}


std::ostream& SingleSourceSolution::output(std::ostream& os) const {
    os << "Single Source Shortest Path from node " << source << ":\n";
    // itera il vettore contenente i nodi
    for (size_t i = 0; i < distances.size(); ++i) {
        // se il nodo corrente è il nodo sorgente si salta perchè non è necessario calcolare la distanza
        if (i == source) continue;
        // in questo caso il nodo i non è raggiungibile, il valore rappresenta l'infinito
        if (distances[i] == std::numeric_limits<int>::max()) {
            os << "Node " << i << " is unreachable from source " << source << "\n";
        } else {
            os << "Shortest path to node " << i << " is " << distances[i] << "\n";
        }
    }
    return os;
}

void SingleSourceSolution::exportSolution(const std::string& filename) const {
    std::ofstream file(filename);
  	if (file.is_open()) {
        file << "Single Source Shortest Path from node " << source << ":\n";
        for (size_t i = 0; i < distances.size(); ++i) {
            if (i == source) continue;
            if (distances[i] == std::numeric_limits<int>::max()) {
                file << "Node " << i << " is unreachable from source " << source << "\n";
            } else {
            	file << "Shortest path to node " << i << " is " << distances[i] << "\n";
            }
        }
        file.close();
    }
}

// costruttore
APSPSolution::APSPSolution(const std::vector<std::vector<int>>& distMatrix)
    : distanceMatrix(distMatrix) {}

std::ostream& APSPSolution::output(std::ostream& os) const {
    // dimensione della matrice da stampare in output
    int n = distanceMatrix.size();
    os << "All-Pairs Shortest Paths:" << std::endl;
    // due cicli per iterare le righe e colonne della matrice
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // indica che tra i due nodi in questo punto non esiste un percorso
            if (distanceMatrix[i][j] == std::numeric_limits<int>::max()) {
                os << "INF ";  // utilizzo di INF per indicare che la distanza tra i due nodi non esista 
            } else {
            	// stampa la distanza 
                os << distanceMatrix[i][j] << " ";
            }
        }
        os << std::endl;
    }
    return os;
}

void APSPSolution::exportSolution(const std::string& filename) const {
    std::ofstream file(filename);
    int n = distanceMatrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (distanceMatrix[i][j] == std::numeric_limits<int>::max()) {
                file << "INF ";
            } else {
                file << distanceMatrix[i][j] << " ";
            }
        }
        file << std::endl;
    }
    file.close();
}