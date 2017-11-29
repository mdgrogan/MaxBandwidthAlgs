#include "Graph.h"
#include "MaxHeap.h"

class maxHeapDijkstra {
    public:
	maxHeapDijkstra(Graph graph);
	MaxBWPath Search(int start, int goal);
    private:
	MaxBWPath ReconstructPath();

	Graph G;
	int s;
	int t;
};
