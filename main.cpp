#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h> 
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <map>
#include <queue>
#include "DG.h"

using namespace std;
DGraph* Global_DG;

void file_parser(const char*);
void graph_generator();
void graph_analysis();
void dfs();


int main(int argc, char** argv)     
{
    if( argc == 1 )
    {
        graph_generator();
    }
    else if( argc == 2 )
    {
        file_parser(argv[1]);
        
    }
    

	//Global_DG -> levelization();
	//Global_DG->print_status();

    return 0;
}

void file_parser(const char* gate_file)
{
    string line;
    string com_line;
    size_t find;
    vector< string > line_list;
    map< string, Wire* > wire_list;
    map< string, Gate* > gate_list;
    fstream fgate_file(gate_file);
    Global_DG = new DGraph();

    if (!fgate_file) 
    {
        cout << "open failed..."<< endl; 
        return;    
    }

    while( getline( fgate_file, line ) )
    {
        com_line.append(line);
        find = line.find(";");
        if( find == string::npos )
            continue;
        
        line_list.push_back(com_line);
        com_line = "";
    }

    fgate_file.close();

    
    for( size_t i = 0; i < line_list.size(); i++ )
    {
        line = line_list[i];
        size_t find_i = line.find("input");
        size_t find_o = line.find("output");
        size_t find_w = line.find("wire");

        find = line.find("module");

        if( find != string::npos )
        {
            if( i == 0 )
                Global_DG -> set_module_dec( line );
            continue;
        }

        int wire_type;
        if( find_i != string::npos )
        {
            find = find_i + 5;
            wire_type = 1;
            Global_DG -> set_input_dec( line.substr(find ) );
        }
        else if( find_o != string::npos )
        {
            find = find_o + 6;
            wire_type = 2;
            Global_DG -> set_output_dec( line.substr(find ) );
        }
        else if( find_w != string::npos )
        {
            find = find_w + 4;
            wire_type = 0;
            Global_DG -> set_wire_dec( line.substr(find ) );
        }
        else 
            find = string :: npos;

        if( find != string::npos )
            Global_DG -> build_wire( line.substr(find ) , wire_type );
        else
            Global_DG -> build_gate( line );
    }


    
    
    Global_DG -> input_output_DFF    ();
    Global_DG -> DFF_modification    ();
    Global_DG -> gate_wire_connection();
   
    /*
    for ( map<string ,Wire*>::iterator it= wire_list.begin(); it!= wire_list.end(); ++it)
    {
        cout << it -> second -> get_name() << ":\n";
        cout << "fanin: ";
        for( size_t i = 0; i < it -> second -> fanin_gate_size(); i++ )
            cout << it -> second -> get_fanin_gate( i ) -> get_name() << " ";
        cout << endl;
        cout << "fanout: ";
        for( size_t i = 0; i < it -> second -> fanout_gate_size(); i++ )
            cout << it -> second -> get_fanout_gate( i ) -> get_name() << " ";
        cout << endl;
    }
    cout << endl;
    */
    Global_DG -> DFS_DFF_connection();

    //DFF_levelization  ( gate_list );

    Global_DG -> build_node_connection();


    Global_DG -> find_cycle();
	Global_DG -> find_fvs();
    Global_DG -> Deadlock_elimination(); 
    Global_DG -> DFS_DFF_connection();
    Global_DG -> completion_detection(); 
    Global_DG -> create_c_element_module ();
    Global_DG -> create_NCL_register_module ();
    Global_DG -> create_c_element_rst_module ();
    Global_DG -> create_NCL_register_rst_module ();
	Global_DG -> print_Verilog();


}

void graph_generator (int node_num, float connection_rate)     //node_num should bigger than 5, connection_rate should in 0~1
{
	if (node_num<=5||connection_rate>1||connection_rate<0)
		return;


	vector <Node*> temp_node_list;


	for (int i=0;i<node_num;i++)              //add empty node
	{
		temp_node_list.push_back(new Node(to_string(i),i));
	}	


	Global_DG = new DGraph();
	for (int i=0;i<node_num;i++)
	{
		Global_DG->add_node( temp_node_list[i] );
	}
	cout << "add empty node done" << endl;

	for(int i=0; i<5;i++)				//construct pi connection
	{
		for (int j=5;j<node_num;j++)
		{
			if (rand() / (RAND_MAX + 1.0 ) <connection_rate)
			{
				Global_DG->get_node(i) -> add_fanout( Global_DG->get_node(j) );
				Global_DG->get_node(j) -> add_fanin(  Global_DG->get_node(i) );
				
			}	
		}	
	}

	cout << "construct pi connection done " << endl;
	for(int i=5; i<node_num;i++)			//construct normal node connection
	{
		for (int j=5;j<node_num;j++)
		{
			if (i==j)
				continue;
			else if (rand() / (RAND_MAX + 1.0 ) <connection_rate)
			{
				Global_DG->get_node(i) -> add_fanout( Global_DG->get_node(j) );
				Global_DG->get_node(j) -> add_fanin(  Global_DG->get_node(i) );
				
			}	
		}	
	}



	cout << "generate done" << endl;
	
	
}

void graph_generator()
{
	graph_generator (10,0.4);
	
}


void graph_analysis()
{
}


