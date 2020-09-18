#ifndef _SIMPLIFY_H_
#define _SIMPLIFY_H_

#include "libhead.h"
#include "CRoaring/roaring.hh"

class simplify
{
private:
    vector<vector<Node *> > layers;

    // delete duplicate node, i is the index level of dupl
    void deduplicate(int i, Node *keep, Node *dupl, vector<Roaring> &nbrs);

public:
    simplify(/* args */);
    ~simplify();
    vector<vector<Node *> > &get_layers();

    // replace the node from vector<node *> *nodes with the new_node, which the id of this node is id
    bool replace_node_by_id(vector<Node *> *nodes, Node *new_node, size_t id);

    // clean all wires and bufs from PIs to POs by recusive
    void clean_wire_buf_recusive(vector<Node *> &PIs);

    // clean all wires and bufs from PIs to POs by iterator
    void clean_wire_buf_iterator(vector<Node *> &PIs);

    // reassign id of each node, and layer assigment according to the logic depth, and achieve path balancing
    vector<vector<Node *> > &id_reassign_and_layered(vector<Node *> &PIs, vector<Node *> &POs);

    // reassign id of each node
    void id_reassign(vector<Node *> &PIs);
    void id_reassign();

    // layer assigment according to the logic depth, and achieve path balancing
    vector<vector<Node *> > &layer_assignment(vector<Node *> &PIs, vector<Node *> &POs);

    // merge the equal nodes
    void reduce_repeat_nodes();
    // merge the equal nodes
    void merge_nodes_between_networks();
};

#endif