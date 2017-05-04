#include "DG.h"
#include <iostream>
#include <iomanip>
Node::Node()
{}

Node::~Node() 
{
    fanin_list.clear();
    fanout_list.clear();
}

DGraph::DGraph()
{}

DGraph::~DGraph()
{
    node_list.clear();
}
