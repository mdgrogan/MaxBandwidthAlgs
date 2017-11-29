#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <vector>
#include <cmath>

#include "Node.h"

class MaxHeap {
    public:
	MaxHeap();
	MaxHeap(const std::vector<Node> &v);
	Node operator [](int i) { return items[i]; };  
	void IncreaseKey(int i, int val);
	Node Maximum();
	void Insert(Node n);
	void Delete(int k);
	int Location(int x);
	int size();

    private:
	std::vector<Node> items;
	std::vector<int> index;	    // location of node within items is stored by index
	void BuildHeap();
	void MaxHeapify(int i);
	void SiftUp(int i);
};

#endif
