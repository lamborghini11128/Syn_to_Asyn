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
        Node(string name, int id): name(name), id(id) {}
        ~Node();

    // Graph generation
        void add_fanin(Node* node)  {
            for (int i=0; i!=fanin_list.size(); ++i) {
                if (node->name == fanin_list[i]->name) return;
            }
            fanin_list.push_back(node);
        }
        void add_fanout(Node* node) {
            for (int i=0; i!=fanout_list.size(); ++i) {
                if (node->name == fanout_list[i]->name) return;
            }
            fanout_list.push_back(node);
        }
        vector<Node*>& get_fanin_list() { return fanin_list; }
        vector<Node*>& get_fanout_list() { return fanout_list; }
        string name;
        
    //Detect cycle part
        Node* get_fanin(int i) {return fanin_list[i];}
        Node* get_fanout(int i) {return fanout_list[i];}
        int get_fanin_size() {return fanin_list.size();}
        int get_fanout_size() {return fanout_list.size();}
        Cycle* get_cycle(int i) {return cycle_list[i];}
        void add_cycle(Cycle* c) {cycle_list.push_back(c);}
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
    //Graph generation part
        void add_node(const Node& newNode) { node_list.push_back(newNode); }
        const void print_list() {
            for(int i=0; i!=node_list.size(); ++i) {
                cout << node_list[i].name << endl;
                cout << "   fanin:  ";
                for (int j=0; j<node_list[i].get_fanin_list().size(); ++j) {cout << node_list[i].get_fanin(j)->name << " ";}
                cout << endl << "   fanout: ";
                for (int j=0; j<node_list[i].get_fanout_list().size(); ++j) {cout << node_list[i].get_fanout(j)->name << " ";}
                cout << endl << endl;
            }
        }
        
    //Detect cycle part
        void find_cycle();
        void find_fvs();
        Cycle_list* get_cycle_list() {return cycle_list;}         
        void add_node_to_fvs(Node* n) {fvs.push_back(n);}
        int get_fvs_size() {return fvs.size();}
        Node* get_fvs_node (int i) {return fvs[i];}

    private:
        vector< Node > node_list;           


    //Detect cycle part
        Cycle_list* cycle_list;       //the list of cycle_list, for each cycle_list, cycles in which share some same nodes
        vector<Node*> fvs;
};


#endif
