#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <deque>
#include <iterator>
#include "Node.h"

/* Solution structure */
struct MaxBWPath {
    std::deque<int> path;
    int bw;
};

/* Adjacency list edge */
struct Edge {
    int dest;
    int weight;
};

class Graph {
    public:
	Graph() {};
	Graph(int s, int d);
	std::vector<Node> V;		    // Vertices
	std::vector<std::deque<Edge>> A;    // Adjacency list
    private:
	void InitNodes();
	void AddEdge(int src, int dst);
	void FillEdges();
	bool isGoodEdge(int src, int dst);
	int degree;	// vertex degree
	int size;	// graph size
};

#endif
