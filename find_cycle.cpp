#include "DG.h"
#include "Cycle.h"
#include "Cycle_list.h"
#include <algorithm>
#include <vector>


using namespace std;

void DFS_traverse(Node*, vector<Node*>&, Cycle_list*);

bool nodep_compare (Node* node1, Node* node2)
{
    return (node1->get_cycle_size()>node2->get_cycle_size());
}

void DGraph::find_cycle()
{    

    cout << "Start to find cycle and fvs" << endl;
    //cout << node_list.size() << endl;

    vector <Node*> DFS_start_nodes; 
    //find those node whose indegree==0
    for (int i=0; i<node_list.size();i++)				//initialize DFS information
    {
       node_list[i] -> set_node_DFS_id(-1);
       node_list[i] -> set_traversed_or_not(false);

       if (node_list[i] -> get_fanin_size()==0)
            DFS_start_nodes.push_back( node_list[i] ); 
    }
    for (int i=0; i<DFS_start_nodes.size();i++)				//for each PI, DFS traverse to find cycle
    {
        vector<Node*> DFS_stack;
        DFS_traverse(DFS_start_nodes[i],DFS_stack,cycle_list);
        
    }



}



void DFS_traverse(Node* current_node, vector<Node*>& DFS_stack, Cycle_list* c_l)
{
    //current_node->set_in_stack_or_not(true);
    //cout << "current node id=" << current_node->get_node_id() << "current node DFS id=" << current_node->get_node_DFS_id() << endl;
    //DFS_count+=1;
    //cout<< "current" << current_node << " " << current_node->get_node_id() << endl;
    //cout << DFS_stack[DFS_stack.size()-1] << endl;


    current_node->set_node_DFS_id(DFS_stack.size());			//push node into stack
    DFS_stack.push_back(current_node);
	
    current_node->set_traversed_or_not(true);
	
    for (int i=0;i<current_node->get_fanout_size();i++)
    {
        Node* outnode=current_node->get_fanout(i);
	//cout << "current node id=" << current_node->get_node_id() << "current node DFS id=" << current_node->get_node_DFS_id() << endl;
	//cout << "out node id=" <<  outnode->get_node_id() << "out node DFS id=" << outnode->get_node_DFS_id() << endl; 

        if (outnode->get_node_DFS_id()!=-1)				//if fanout is already in stack, there's cycle in the stack
        {
            //cout << "cycle find!" << endl;
	    //cout << "aa current node id=" << current_node->get_node_id() << "current node DFS id=" << current_node->get_node_DFS_id() << endl;
	    //cout << "aa out node id=" <<  outnode->get_node_id() << "out node DFS id=" << outnode->get_node_DFS_id() << endl; 
            Cycle* cycle=new Cycle(); 
            c_l->add_cycle(cycle);
            for (int j=outnode->get_node_DFS_id();j<DFS_stack.size();j++)
            {
		//cout << DFS_stack[j] << endl;
                DFS_stack[j]->add_cycle(cycle);
		//cout << "cc" <<  DFS_stack[j]->get_cycle_size() << endl;
                cycle->add_node(DFS_stack[j]);
            }
            
        }
        if (outnode->get_traversed_or_not()==false)			//recursively to next node
        {
           DFS_traverse(outnode,DFS_stack,c_l); 
        }
        
    }
    DFS_stack.pop_back();						//pop from stack
    current_node->set_node_DFS_id(-1);
    


}

void DGraph::find_fvs()
{
    vector <Node*> sorted_node;
    for (int i=0;i<node_list.size();i++)
    {
    	//cout << node_list[i].get_cycle_size() << endl;
        sorted_node.push_back( node_list[i] );
    	//cout << &node_list[i] << endl;
    	//cout << (&node_list[i])->get_cycle_size() << endl;
    }
    sort(sorted_node.begin(),sorted_node.end(),nodep_compare);		//sort by the cycle num which contain the node

    int broken_cycle_count=0,i=0;
    if (cycle_list==NULL)
        return;
    while (broken_cycle_count!=cycle_list->get_size())			//add to fvs until all cycle broken
    {
        bool is_added=false;
    	//cout << "bb" << sorted_node[i]->get_cycle_size() << endl;
        for (int j=0;j<sorted_node[i]->get_cycle_size();j++)
        {
	
		//cout << "abc" <<  sorted_node[i]->get_cycle_size() << endl;
            if (sorted_node[i]->get_cycle(j)->get_is_broken()==false)
            {
                sorted_node[i]->get_cycle(j)->set_is_broken(true);
                broken_cycle_count+=1;
    	        //cout << "broken_count" << broken_cycle_count << endl;
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


void DGraph::print_status()
{
	for (int i=0;i<node_list.size();i++)
	{
		cout << "Node_id:" << node_list[i] -> get_node_id()<< endl;	
		cout << "Node_id:" << node_list[i]<< endl;	
		cout << "fanin:" << endl;	
		for (int j=0;j<node_list[i] -> get_fanin_size();j++)
		{
			cout << node_list[i] -> get_fanin(j) << " ";
			cout << node_list[i] -> get_fanin(j)->get_node_id() << " ";
		}
		cout << endl;
		cout << "fanout:" << endl;	
		for (int j=0;j<node_list[i] -> get_fanout_size();j++)
		{
			cout << node_list[i] -> get_fanout(j) << " ";
			cout << node_list[i] -> get_fanout(j)->get_node_id() << " ";
		}
		cout << endl;
	}
	cout << "############################################" <<endl;

	for (int i=0;i<cycle_list->get_size();i++)
	{
		cout << "cycle_id:" << i <<endl;
		cout << "node:" <<endl;
		for (int j=0;j<cycle_list->get_cycle(i)->get_size();j++)
			cout << cycle_list->get_cycle(i)->get_node(j)->get_node_id() << " ";
		cout << endl;
		
	}
	cout << "############################################" <<endl;
	cout << "fvs:" << endl;
	for (int i=0;i<fvs.size();i++)
	{
		cout << fvs[i]->get_node_id() << " "  << endl;
		
	}



}
