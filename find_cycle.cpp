#include "DG.h"
#include "Cycle.h"
#include "Cycle_list.h"
#include <algorithm>
#include <vector>


using namespace std;

void DFS_traverse(Node*, vector<Node*>&, Cycle_list*);

bool nodep_compare (Node* node1, Node* node2)
{
    return (node1->get_cycle_size()<node2->get_cycle_size());
}

void DGraph::find_cycle()
{    

    cout << "Start to find cycle and fvs" << endl;
    cout << node_list.size() << endl;

    vector <Node*> DFS_start_nodes; 
    //find those node whose indegree==0
    for (int i=0; i<node_list.size();i++)
    {
       node_list[i].set_node_DFS_id(-1);
       node_list[i].set_traversed_or_not(false);

       if (node_list[i].get_fanin_size()==0)
            DFS_start_nodes.push_back(&node_list[i]); 
    }
    //DFS_count=0; 
    for (int i=0; i<DFS_start_nodes.size();i++)
    {
        vector<Node*> DFS_stack;
        DFS_traverse(DFS_start_nodes[i],DFS_stack,cycle_list);
        //clear flag of node in stack (auto?)
        
    }



}



void DFS_traverse(Node* current_node, vector<Node*>& DFS_stack, Cycle_list* c_l)
{
    //current_node->set_in_stack_or_not(true);
    current_node->set_node_DFS_id(DFS_stack.size());
    //DFS_count+=1;
    DFS_stack.push_back(current_node);
    current_node->set_traversed_or_not(true);
    cout<< current_node->get_fanout_size() << endl;
    for (int i=0;i<current_node->get_fanout_size();i++)
    {
        Node* outnode=current_node->get_fanout(i);
	//cout << "out node id=" <<  outnode->get_node_id() << "out node DFS id=" << outnode->get_node_DFS_id() << endl; 
        if (outnode->get_node_DFS_id()!=-1)
        {
            cout << "cycle find!" << endl;
	    cout << "current node id=" << current_node->get_node_id() << "current node DFS id=" << current_node->get_node_DFS_id() << endl;
	    cout << "out node id=" <<  outnode->get_node_id() << "out node DFS id=" << outnode->get_node_DFS_id() << endl; 
	    //cout << "current node id=" << current_node->get_node_id() << "current node DFS id=" << current_node->get_node_DFS_id() << endl;
	    //cout << "out node id=" <<  outnode->get_node_id() << "out node DFS id=" << outnode->get_node_DFS_id() << endl; 
            Cycle* cycle=new Cycle(); 
            c_l->add_cycle(cycle);
            for (int j=outnode->get_node_DFS_id();j<DFS_stack.size();j++)
            {
                DFS_stack[j]->add_cycle(cycle);
                cycle->add_node(DFS_stack[j]);
            }
            
        }
        if (outnode->get_traversed_or_not()==false)
        {
           DFS_traverse(outnode,DFS_stack,c_l); 
        }
        
    }
    DFS_stack.pop_back();
    current_node->set_node_DFS_id(-1);
    


}

void DGraph::find_fvs()
{
    vector <Node*> sorted_node;
    for (int i=0;i<node_list.size();i++)
    {
        sorted_node.push_back(&node_list[i]);
    }
    sort(sorted_node.begin(),sorted_node.end(),nodep_compare);
    int broken_cycle_count=0,i=0;
    if (cycle_list==NULL)
        return;
    while (broken_cycle_count!=cycle_list->get_size())
    {
        bool is_added=false;
        //cout<< sorted_node[i]->get_cycle_size() << endl;   
        for (int j=0;j<sorted_node[i]->get_cycle_size();j++)
        {
            if (sorted_node[i]->get_cycle(j)->get_is_broken()==false)
            {
                sorted_node[i]->get_cycle(j)->set_is_broken(true);
                broken_cycle_count+=1;
                if (is_added==false)
                {
                    fvs.push_back(sorted_node[i]);
                    is_added=true;
                }
            }
        }
        i+=1;
    }


}


