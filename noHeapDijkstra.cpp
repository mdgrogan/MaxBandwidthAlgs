#include <iostream>
#include <climits>
#include "noHeapDijkstra.h"

noHeapDijkstra::noHeapDijkstra(Graph graph) {
    G = graph;
}

MaxBWPath noHeapDijkstra::Search(int start, int goal) {
    /* status is set by graph constructor */
    s = start;
    t = goal;
    G.V[s].status = INTREE;
    G.V[s].value = INT_MAX;
    G.V[s].parent = NULL;
    
    for (auto it=G.A[s].begin(); it != G.A[s].end(); it++) {
	G.V[it->dest].status = FRINGE;
	G.V[it->dest].parent = &G.V[s];
	G.V[it->dest].value = it->weight;
    }

    while (G.V[t].status != INTREE) {
	int max = 0;
	for (int i=1; i<=G.V.size(); i++) {
	    if ((G.V[max].value < G.V[i].value) && (G.V[i].status == FRINGE)) {
		max = i;
	    }
	}

	G.V[max].status = INTREE;

	for (auto it=G.A[G.V[max].label].begin(); it != G.A[G.V[max].label].end(); it++) {
	    int tmp = (G.V[G.V[max].label].value < it->weight) 
		    ? G.V[G.V[max].label].value : it->weight;
	    if (G.V[it->dest].status == UNSEEN) {
		G.V[it->dest].status = FRINGE;
		G.V[it->dest].parent = &G.V[G.V[max].label];
		G.V[it->dest].value = tmp;
	    } else if ((G.V[it->dest].status == FRINGE) && (G.V[it->dest].value < tmp)) {
		G.V[it->dest].parent = &G.V[G.V[max].label];
		G.V[it->dest].value = tmp;
	    }
	}
    }
    return ReconstructPath();
}

MaxBWPath noHeapDijkstra::ReconstructPath() {

    std::deque<int> path;
    path.push_front(G.V[t].label);
    Node *p = G.V[t].parent;
    while (p) {
	path.push_front(p->label);
	p = p->parent;
    }
    return {path, G.V[t].value};
}
