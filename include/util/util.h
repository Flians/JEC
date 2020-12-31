#ifndef _UTIL_H_
#define _UTIL_H_

#include "node.h"

// delete the node, return its parent
Node *delete_node(Node *node);

// merge two nodes
void merge_node(Node *node, Node *repeat);

void unique_element_in_vector(vector<Node *> &v);

#endif