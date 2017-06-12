#include "DG.h"
#include "Cycle_list.h"
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
{
    cycle_list=new Cycle_list();
}

DGraph::~DGraph()
{
    for (int i=0;i<cycle_list->get_size();i++)
    {
        delete cycle_list->get_cycle(i);
    }
    delete cycle_list;
    
    node_list.clear();
}
