#include <iomanip>
#include <iostream>
#include <vector>
#ifndef DG_H
#define DG_H
using namespace std;

class Node
{
    public:
        Node();
        ~Node();

    private:
        vector< Node*>  fanout_list;
        vector< Node*>  fanin_list;
};



// directed graph
class DGraph
{
    public:
        DGraph();
        ~DGraph();

    private:
        vector< Node > node_list;
};


#endif
