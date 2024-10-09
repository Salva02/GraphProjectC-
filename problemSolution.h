#ifndef PROBLEMSOLUTION_H
#define PROBLEMSOLUTION_H

#include <iostream>
#include <vector>
#include "graph.h"
using namespace std;

class ProblemSolution {

public:
	virtual ~ProblemSolution() = default;
	virtual std::ostream& output(std::ostream& os) const = 0;
	virtual void exportSolution(const std::string& filename) const = 0;
};

class MST : public ProblemSolution {

	vector<Graph::Edge> mstEdges;
	int totalWeight;

public:
	MST(const vector<Graph::Edge>& edges, int weight);
	
	std::ostream& output(std::ostream& os) const override;
	
	void exportSolution(const std::string& filename) const override;
    
};

class ShortestPathSolution : public ProblemSolution {
public:
    ShortestPathSolution(const std::vector<int>& path, int distance);

    std::ostream& output(std::ostream& os) const override;

    void exportSolution(const std::string& filename) const override;
       
private:
    std::vector<int> shortestPath;
    int shortestDistance;
};

class SingleSourceSolution : public ProblemSolution {

	std::vector<int> distances;
	std::vector<int> previous;
	int source;

public:
	SingleSourceSolution(const std::vector<int>& dist, const std::vector<int>& prev, int src);

	std::ostream& output(std::ostream& os) const override;

	void exportSolution(const std::string& filename) const override;
};

class APSPSolution : public ProblemSolution { // All pairs shortest path
public:
    APSPSolution(const std::vector<std::vector<int>>& distMatrix);

    std::ostream& output(std::ostream& os) const override;
    void exportSolution(const std::string& filename) const override;

private:
    std::vector<std::vector<int>> distanceMatrix;
};

#endif