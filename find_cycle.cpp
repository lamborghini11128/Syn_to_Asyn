#include "DG.h"
#include "Cycle.h"
#include "Cycle_list.h"


using namespace std;

void DFS_traverse(Node*, vector<Node*>&, vector<Cycle_list*>&);


void DGraph::find_cycle()
{    



    vector <Node*> DFS_start_nodes; 
    //find those node whose indegree==0
    for (int i=0; i<node_list.size();i++)
    {
       node_list[i].set_node_id(-1);
       if (node_list[i].get_fanin_size()==0)
            DFS_start_nodes.push_back(&node_list[i]); 
    }
    //DFS_count=0; 
    for (int i=0; i<DFS_start_nodes.size();i++)
    {
        vector<Node*> DFS_stack;
        DFS_traverse(DFS_start_nodes[i],DFS_stack,cycle_list_list);
        //clear flag of node in stack (auto?)
        
    }



}




void DFS_traverse(Node* current_node, vector<Node*>& DFS_stack, vector<Cycle_list*>& c_l_l)
{
    //current_node->set_in_stack_or_not(true);
    current_node->set_node_id(DFS_stack.size());
    //DFS_count+=1;
    DFS_stack.push_back(current_node);
    current_node->set_traversed_or_not(true);
    for (int i=0;i<current_node->get_fanout_size();i++)
    {
        Node* outnode=current_node->get_fanout(i);
        if (outnode->get_node_id()!=-1)
        {
            Cycle* cycle=new Cycle(); 
            for (int j=outnode->get_node_id();j<DFS_stack.size();j++)
            {
                if (outnode->get_cycle_size()!=0)
                {
                    Cycle_list* cycle_list=outnode->get_cycle(0)->get_cycle_list();
                    cycle_list->add_cycle(cycle);
                    cycle->set_cycle_list(cycle_list);
                }
                cycle->add_node(DFS_stack[j]);
                if (j==DFS_stack.size()&&cycle->get_cycle_list()==NULL)
                {
                    Cycle_list* cycle_list = new Cycle_list();
                    cycle_list->add_cycle(cycle);
                    cycle->set_cycle_list(cycle_list);
                    c_l_l.push_back(cycle_list);
                }
                
                
                
            }

            
            
            
        }
        else if (outnode->get_traversed_or_not()==false)
        {
           DFS_traverse(outnode,DFS_stack,c_l_l); 
        }
        
    }
    DFS_stack.pop_back();
    current_node->set_node_id(-1);
    


}
