#include <iostream>
#include <climits>
#include "maxHeapDijkstra.h"


maxHeapDijkstra::maxHeapDijkstra(Graph graph) {
    G = graph;
}

MaxBWPath maxHeapDijkstra::Search(int start, int goal) {
    /* Vertices initialized by graph constructor */
    s = start;
    t = goal;
    G.V[s].value = INT_MAX;

    MaxHeap Q(G.V);


    while (Q.size() != 0) {
	Node u =  Q.Maximum();
	Q.Delete(1);
	if (u.label == G.V[t].label) {
	    return ReconstructPath();
	}
	for (auto it=G.A[u.label].begin(); it != G.A[u.label].end(); it++) {
	    int tmp = (u.value < it->weight) ? u.value : it->weight;
	    if (G.V[it->dest].value < tmp) {
		Q.IncreaseKey(Q.Location(it->dest), tmp);
		G.V[it->dest].value = tmp;
		G.V[it->dest].parent = &G.V[u.label];
	    }
	}
    }
}

MaxBWPath maxHeapDijkstra::ReconstructPath() {
    std::deque<int> path;
    path.push_front(G.V[t].label);
    Node *p = G.V[t].parent;
    while (p) {
	path.push_front(p->label);
	p = p->parent;
    }
    return {path, G.V[t].value};
}
