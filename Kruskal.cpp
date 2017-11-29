#include "Kruskal.h"

Kruskal::Kruskal(Graph graph) {
    G = graph;
    size = 0;
}

/*******************************************************************
 * Recursively put edges into heap order
********************************************************************/
void Kruskal::MaxHeapify(int i) {
    int l = 2*i;
    int r = 2*i + 1;
    int largest;
    if ((l <= size) && (E[i].weight < E[l].weight)) {
        largest = l;
    } else {
	largest = i;
    }
    if ((r <= size) && (E[largest].weight < E[r].weight)) {
        largest = r;
    }
    if (largest != i) {
        k_edge tmp = E[i];
        E[i] = E[largest];
        E[largest] = tmp;

	MaxHeapify(largest);
    }
}

/*******************************************************************
 * Sift edge upwards
********************************************************************/
void Kruskal::SiftUp(int i) {
    while ((i > 1) && (E[i/2].weight < E[i].weight)) {
	    k_edge tmp = E[i];
	    E[i] = E[i/2];
	    E[i/2] = tmp;
	i = i/2;
    }
}

/*******************************************************************
 * Insert
********************************************************************/
void Kruskal::Insert(k_edge e) {
    E.push_back(e);
    size++;
    SiftUp(size);
}

/*******************************************************************
 * Return maximum weighted edge
********************************************************************/
k_edge Kruskal::Maximum() {
    if (E.empty()) {
	return {-1, {-1, -1}};
    }
    return E[1];
}

/*******************************************************************
 * Delete
********************************************************************/
void Kruskal::Delete(int k) {
    // '1' indexing..
    if (k == 0) {
	return;
    }
    E[k] = E[size];
    size--;
    E.pop_back();
    MaxHeapify(k);
}

/*******************************************************************
 * Convert edges from adjacency list into max heap and then create
 * a maximum spanning tree using Kruskal's algorithm
********************************************************************/
void Kruskal::MakeMST() {
    T.V = G.V;
    E.push_back({0, {0, 0}});
    for (int src=1; src<G.V.size(); src++) {
	for (auto j=G.A[src].begin(); j != G.A[src].end(); j++) {
	    int dst = j->dest;
	    k_edge e = {j->weight, {src, dst}};
	    Insert(e);

	    // Naive way to remove duplicates. Bad for performance
	    /*for (auto k=G.A[dst].begin(); k != G.A[dst].end(); k++) {
		if (k->dest == src) {
		    G.A[dst].erase(k);
		    break;
		}
	    }*/
	}
    }

    // Kruskal
    T.A.resize(T.V.size());
    Rank.resize(E.size());
    Parent.resize(E.size());
    // Since edges are labled consecutively, this is ok
    for (int i=1; i < Rank.size(); i++) {
	MakeSet(i);
    }
    // A tree has no more than n-1 edges, so that is our limit.
    // the extra '-1' is to account for '1' indexing
    int vCount = (T.V.size()-1)-1;
    for (int i=0; i < vCount;) {
	k_edge k = Maximum();
	Delete(1);
	int u = k.endpoints.first;
	int v = k.endpoints.second;
	int ru = Find(u);
	int rv = Find(v);
	if (ru != rv) {
	    Union(ru, rv);
	    T.A[u].push_front({v, k.weight});
	    T.A[v].push_front({u, k.weight});
	    i++;
	}
    }
}

/*******************************************************************
 * Makset
********************************************************************/
void Kruskal::MakeSet(int i) {
    Rank[i] = 0;
    Parent[i] = i;
}

/*******************************************************************
 * Union-by-Rank
********************************************************************/
void Kruskal::Union(int r1, int r2) {
    if (Rank[r1] < Rank[r2]) {
	Parent[r2] = r1;
    } else if (Rank[r1] > Rank[r2]) {
	Parent[r1] = r2;
    } else {
	Parent[r1] = r2;
	Rank[r2]++;
    }
}

/*******************************************************************
 * Find with path compression
********************************************************************/
int Kruskal::Find(int x) {
    if (x != Parent[x]) {
	Parent[x] = Find(Parent[x]);
    }
    return Parent[x];
}

/*******************************************************************
 * Depth first search
********************************************************************/
void Kruskal::DFS(int v) {
    T.V[v].status = FRINGE;
    for (auto it=T.A[v].begin(); it != T.A[v].end(); it++) {
	if (T.V[it->dest].status == UNSEEN) {
	    T.V[it->dest].parent = &T.V[v];
	    T.V[it->dest].value = it->weight;
	    if (it->dest == t) {
		break;
	    }
	    DFS(it->dest);
	}
    }
    T.V[v].status = INTREE;
}

/*******************************************************************
 * Make max spanning tree, search it, and reconstruct path
********************************************************************/
MaxBWPath Kruskal::FindPath(int start, int goal) {
    s = start;
    t = goal;
    MakeMST();
    T.V[s].value = INT_MAX;
    DFS(s);
    
    std::deque<int> path;
    path.push_front(T.V[t].label);
    Node *p = T.V[t].parent;
    int bw = T.V[t].value;
    while (p) {
	path.push_front(p->label);
	if (p->value < bw) {
	    bw = p->value;
	}
	p = p->parent;
    }
    return {path, bw};
}
