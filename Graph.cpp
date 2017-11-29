#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Graph.h"

/* Calling this with d>=s-1 acts really weird obviously */
Graph::Graph(int s, int d) {
    srand(time(0));
    degree = d;
    size = s+1;
    //size = s;
    InitNodes();
    A.resize(size);
    FillEdges();
}
/********************************************************************
 * Fill vertex list with default initialized nodes
*********************************************************************/
void Graph::InitNodes() {
    V.push_back({0,0,0, NULL});
    for (int i=1; i<size; i++) {
	V.push_back({i, 0, UNSEEN, NULL});
    }
}

/********************************************************************
 * Randomly assign edges based on vertex degree and graph size
*********************************************************************/
void Graph::FillEdges() {
    for (int src = 1; src < size; src++) {
	for (int dst = src+1; dst < size; dst++) {
	    if ((rand()%10000) < ((double)(degree-2)/(double)size * 10000)) {
		AddEdge(src, dst);
	    }
	}
    }
    // This step ensures a connected graph
    for (int i=1; i<size; i++) {
	if (i+1 < size) {
	    if (isGoodEdge(i, i+1)) {
		AddEdge(i, i+1);
	    }
	}
    }
}

/********************************************************************
 * Check if edge is legal
*********************************************************************/
bool Graph::isGoodEdge(int src, int dst) {
    if (src == dst) {
        return false;
    }
    for (auto it=A[src].begin(); it != A[src].end(); it++) {
	if (it->dest == dst) {
	    return false;
	}
    }
    return true;
}

/********************************************************************
 * Add edge to adjacency list with randomized value
*********************************************************************/
void Graph::AddEdge(int src, int dst) {
    Edge e;
    e.dest = dst;
    e.weight = rand()%(2*size)+1;
    A[src].push_back(e);
    e.dest = src;
    A[dst].push_back(e);
}

