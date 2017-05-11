#include <iomanip>
#include <iostream>
#include <vector>
#include "Cycle.h"
#include "Cycle_list.h"
#ifndef DG_H
#define DG_H
using namespace std;

class Node
{
    public:
        Node();
        ~Node();


    //Detect cycle part
        Node* get_fanin(int i) {return fanin_list[i];}
        Node* get_fanout(int i) {return fanout_list[i];}
        int get_fanin_size() {return fanin_list.size();}
        int get_fanout_size() {return fanout_list.size();}
        Cycle* get_cycle(int i) {return cycle_list[i];}
        int get_cycle_size() {return cycle_list.size();}
        void set_node_id (int i) {id=i;}
        int get_node_id () {return id;}
        void set_in_stack_or_not (bool s) {in_stack_or_not=s;}
        bool get_in_stack_or_not () {return in_stack_or_not;}
        //void set_in_cycle_or_not (bool c) {in_cycle_or_not=c;}
        //bool get_in_cycle_or_not () {return in_cycle_or_not;}
        void set_traversed_or_not (bool t) {traversed_or_not=t;}
        bool get_traversed_or_not () {return traversed_or_not;}
        
    
    

    private:
        vector< Node*>  fanout_list;
        vector< Node*>  fanin_list;
    
    
    //Detect cycle part
        vector <Cycle*> cycle_list;         //cycles that contain the node
        int id;                             //DFS id in stack
        bool in_stack_or_not;               //flag indicate that the node is currently in stack or not
        bool in_cycle_or_not;               //flag indicate that the node is currently in cycle or not
        bool traversed_or_not;              //flag indicate that the node is traversed or not
        
};



// directed graph
class DGraph
{
    public:
        DGraph();
        ~DGraph();
        void add_Node(const Node& newNode) { node_list.push_back(newNode); }
        
    //Detect cycle part
        void find_cycle();
        vector<Cycle_list*> get_cycle_list_list() {return cycle_list_list;}         

    private:
        vector< Node > node_list;           


    //Detect cycle part
        vector< Cycle_list*> cycle_list_list;       //the list of cycle_list, for each cycle_list, cycles in which share some same nodes
};


#endif
