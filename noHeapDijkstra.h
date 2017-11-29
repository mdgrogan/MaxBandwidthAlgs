#ifndef NOHEAPDIJKSTRA_H
#define NOHEAPDIJKSTRA_H

#include "Graph.h"

class noHeapDijkstra {
    public:
	noHeapDijkstra(Graph graph);
	MaxBWPath Search(int start, int goal);
    private:
	MaxBWPath ReconstructPath();

	Graph G;
	int s;
	int t;
};

#endif
