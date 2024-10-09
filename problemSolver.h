#ifndef PROBLEMSOLVER_H
#define PROBLEMSOLVER_H
#include "graph.h"
#include "problemSolution.h"
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>
#include <algorithm>
using namespace std;

class ProblemSolver {
public:
    virtual ~ProblemSolver() = default;
    virtual ProblemSolution* solve(const Graph&) = 0;
};

class MSTSolver : public ProblemSolver {

    ~MSTSolver() = default;

	int find(int u, vector<int>& parent);

	void unionSets(int u, int v, vector<int>& parent, vector<int>& rank);

    ProblemSolution* solve(const Graph& graph) override;
};

class SPSPSolver : public ProblemSolver { //SinglePairShortestPath

    public:

    ~SPSPSolver() = default;
    
    SPSPSolver(int src, int dest);

    ProblemSolution* solve(const Graph& graph) override;

    ProblemSolution* solve(const Graph& graph, int source, int destination);

private:
    int source;
    int destination;
}; 

class SingleSourceSolver : public ProblemSolver {
public:

    ~SingleSourceSolver() = default;

    SingleSourceSolver(int src);

    ProblemSolution* solve(const Graph& graph) override;

    ProblemSolution* solve(const Graph& graph, int source, int destination = -1);

private:
int source;

};

class APSPSolver : public ProblemSolver { // All-Pairs Shortest Path
public:

    ~APSPSolver() = default;

    ProblemSolution* solve(const Graph& graph) override;
};


#endif