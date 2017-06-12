#include <vector>
#include <cstddef>

using namespace std;

#ifndef CYCLE_H
#define CYCLE_H


class Cycle_list;
class Node;

class Cycle
{
    public:
        Cycle()  {cycle_list=NULL; is_broken=false;}
        ~Cycle();
        //vector<int> get_nodes_id {return nodes_id;}
        void set_cycle_list(Cycle_list* c) {cycle_list=c;}
        Cycle_list* get_cycle_list() {return cycle_list;}
        void  add_node(Node* n) {node_list.push_back(n);}
        Node* get_node (int i) {return node_list[i];}
        int get_size() {return node_list.size();}
        bool get_is_broken() {return is_broken;}
        void set_is_broken(bool b) {is_broken=b;}

    private:
        //vector<int> nodes_id;
        Cycle_list* cycle_list;
        vector <Node*> node_list;
        bool is_broken;


};

#endif
