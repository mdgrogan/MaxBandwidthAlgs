#include <iostream>
#include <utility>
#include <vector>
#include <climits>
#include <ctime>
#include "Graph.h"

struct k_edge {
    int weight;
    std::pair<int, int> endpoints;
};

class Kruskal {
    public:
	Kruskal(Graph graph);
	MaxBWPath FindPath(int start, int goal);

	std::vector<k_edge> E;	// heap-able edge container

    private:
	/* For Heapsort */
	void MaxHeapify(int i);
	void SiftUp(int i);
	void Insert(k_edge e);
	k_edge Maximum();
	void Delete(int k);
	int size;

	/* For spanning tree */
	void MakeMST();
	void MakeSet(int i);
	void Union(int r1, int r2);
	int Find(int x);
	std::vector<int> Rank;
	std::vector<int> Parent;

	/* Search of tree */
	void DFS(int v);

	Graph T;
	Graph G;
	int s;
	int t;
};
