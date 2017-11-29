#include <iostream>
#include "MaxHeap.h"

MaxHeap::MaxHeap(const std::vector<Node> &v) {
    // expects '1' indexed input
    for (int i=0; i < v.size(); i++) {
	items.push_back(v[i]);
	index.push_back(v[i].label);
    }
    BuildHeap();
}

/********************************************************************
 * Build heap
*********************************************************************/
void MaxHeap::BuildHeap() {
    //for (int i=std::floor(items.size()/2); i>=1; --i) {
    for (int i=size()/2; i>=1; --i) {
	MaxHeapify(i);
    }
}

/********************************************************************
 * Recursively put nodes in heap order
*********************************************************************/
void MaxHeap::MaxHeapify(int i) {
    int l = 2*i;
    int r = 2*i + 1;
    int largest;
    if ((l <= size()) && (items[i].value < items[l].value)) {
        largest = l;
    } else {
	largest = i;
    }
    if ((r <= size()) && (items[largest].value < items[r].value)) {
        largest = r;
    }
    if (largest != i) {
        int tmp1 = index[items[i].label];
        Node tmp2 = items[i];
        index[items[i].label] = index[items[largest].label];
        items[i] = items[largest];
        index[items[largest].label] = tmp1;
        items[largest] = tmp2;

	MaxHeapify(largest);
    }
}

/********************************************************************
 * Sift node upward
*********************************************************************/
void MaxHeap::SiftUp(int i) {
    while ((i > 1) && (items[i/2].value < items[i].value)) {
	    int tmp1 = index[items[i].label];
	    Node tmp2 = items[i];
	    index[items[i].label] = index[items[i/2].label];
	    items[i] = items[i/2];
	    index[items[i/2].label] = tmp1;
	    items[i/2] = tmp2;
	i = i/2;
    }
}

/********************************************************************
 * Change the value of node at location i to val and sift up
*********************************************************************/
void MaxHeap::IncreaseKey(int i, int val) {
    if (val < items[i].value) {
	std::cout<<"New value smaller than old!"<<std::endl;
	return;
    }
    items[i].value = val;
    SiftUp(i);
}

/********************************************************************
 * Max
*********************************************************************/
Node MaxHeap::Maximum() {
    if (items.empty()) {
	return {-1, -1};
    }
    return items[1];
}

/********************************************************************
 * Insert and sift up
*********************************************************************/
void MaxHeap::Insert(Node n) {
    items.push_back(n);
    index.push_back(n.label);
    SiftUp(size());
}

/********************************************************************
 * Delete and re-heapify
*********************************************************************/
void MaxHeap::Delete(int k) {
    // '1' indexing..
    if (k == 0) {
	return;
    }
    index[items[size()].label] = k;
    items[k] = items[size()];
    items.pop_back();
    MaxHeapify(k);
}

/********************************************************************
 * Return the heap location of a node labeled x
*********************************************************************/
int MaxHeap::Location(int x) {
    return index[x];
}

/********************************************************************
 * Return heap size
*********************************************************************/
int MaxHeap::size() {
    // '1' indexing..
    return items.size() - 1;
}
