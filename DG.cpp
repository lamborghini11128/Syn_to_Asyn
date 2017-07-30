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

void DGraph::levelization()
{
    Node* curnode;
    for( size_t i = 0; i < node_list.size(); ++i )
    {
        curnode = node_list[i];
        if( curnode -> get_fanin_size() == 0 )
            curnode -> set_level( 1 );
        else
            curnode -> set_level(-1);
    }

    for( size_t i = 0; i < fvs.size(); ++i )
        fvs[i] -> set_level(0);

    bool update_level = true;
    while( update_level )
    {
        update_level = false;
        for( size_t i = 0; i < node_list.size(); ++i )
        {
            curnode = node_list[i];
            if( curnode -> get_level() != -1 )
                continue;
            int Max_level = -1;
            int temp_level;
            for( size_t j = 0; j < curnode -> get_fanin_size(); ++j )
            {
                temp_level = curnode -> get_fanin(j) -> get_level();
                if( temp_level > Max_level )
                    Max_level = temp_level;
                if( temp_level == -1 )
                {
                    Max_level = -1;
                    break;
                }
            
            }
            if( Max_level != -1 )
            {
                curnode -> set_level( ++Max_level );
                update_level = true;
            }
        }
    }

    for( int i = 0; ;i++)
    {
        cout << "LEVEL " << i << ":\n";
        int counter = 0;
        for( size_t j = 0; j < node_list.size(); ++j )
        {
            if( node_list[j] -> get_level() == i )
            {
                cout << node_list[j] -> name << endl;
                ++counter;
            }
        }
        cout << endl;
        if( counter == 0 )
            break;
    }

}
