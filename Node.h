#ifndef NODE_H
#define NODE_H

/* Node states */
#define UNSEEN 0
#define FRINGE 1
#define INTREE 2

struct Node {
    int label;
    int value;
    int status;
    Node *parent;
};

#endif
