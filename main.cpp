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
#include "module.h"

using namespace std;
DGraph* Global_DG;

void file_parser(const char*);
void graph_generator();
void graph_analysis();
void dfs();
void build_wire( string , map< string, Wire* >&, int& );
void build_gate( string , map< string, Gate* >& , map< string, Wire* >& );
void new_wire( string , map< string, Wire* >&, int );
void gate_add_fanin( Gate* g, Wire* w );
void gate_add_fanout( Gate* g, Wire* w );
void input_output_DFF( map< string, Gate* >&, map< string, Wire*> & );
void print_gate( map< string, Gate* >& );
void DFF_modification( map< string, Gate* >&, map< string, Wire*> & );
void gate_wire_connection( map< string, Gate* >&, map< string, Wire*> & );

void add_AND_gate( map< string, Gate* >&, string, Wire*, Wire*, Wire* );
void add_OR_gate ( map< string, Gate* >&, string, Wire*, Wire*, Wire* );
void add_DFF_gate( map< string, Gate* >&, string, Wire*, Wire*, Wire* );
void add_INV_gate( map< string, Gate* >&, string, Wire*, Wire* );
void DFS_DFF_connection( map< string, Gate* >& );
void DFF_connection( Gate*, vector< Gate* >& );
void DFF_levelization( map< string, Gate* >& );
void Deadlock_elimination( map< string, Gate* > &, map< string, Wire* > & );


string CLKNAME = "clk";
int main(int argc, char** argv)     
{
    if( argc == 1 )
    {
        graph_generator();
	    Global_DG->find_cycle();
	    Global_DG->find_fvs();
	    Global_DG->print_status();
    }
    else if( argc == 2 )
    {
        file_parser(argv[1]);
    }
    
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
            continue;

        int wire_type;
        if( find_i != string::npos )
        {
            find = find_i + 5;
            wire_type = 1;
        }
        else if( find_o != string::npos )
        {
            find = find_o + 6;
            wire_type = 2;
        }
        else if( find_w != string::npos )
        {
            find = find_w + 4;
            wire_type = 0;
        }
        else 
            find = string :: npos;

        if( find != string::npos )
            build_wire( line.substr(find ) , wire_list, wire_type );
        else
            build_gate( line , gate_list, wire_list );
    }


    
    
    input_output_DFF    ( gate_list, wire_list );
    DFF_modification    ( gate_list, wire_list );
    gate_wire_connection( gate_list, wire_list );
   
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
    DFS_DFF_connection( gate_list );

    Deadlock_elimination( gate_list, wire_list ); 
    //DFF_levelization  ( gate_list );

    
    print_gate( gate_list );

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
		Global_DG->add_node(*(temp_node_list[i]));
	}
	cout << "add empty node done" << endl;

	for(int i=0; i<5;i++)				//construct pi connection
	{
		for (int j=5;j<node_num;j++)
		{
			if (rand() / (RAND_MAX + 1.0 ) <connection_rate)
			{
				Global_DG->get_node(i).add_fanout(&(Global_DG->get_node(j)));
				Global_DG->get_node(j).add_fanin(&(Global_DG->get_node(i)));
				
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
				Global_DG->get_node(i).add_fanout(&(Global_DG->get_node(j)));
				Global_DG->get_node(j).add_fanin(&(Global_DG->get_node(i)));
				
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


void build_wire( string s, map< string, Wire* >& m, int& wire_type)
{
    size_t find_l = s.find("[");
    size_t find_m = s.find(":");
    size_t find_r = s.find("]");
    char* pch;
    char* str = new char[ s.size() + 1 ];

    if( find_l == string::npos && find_m == string::npos && find_r == string::npos )
    {
        strcpy( str, s.c_str());
        pch = strtok ( str, " ,;");
        while (pch != NULL)
        {
            string wire_name(pch);
            //Wire* wire = new Wire( wire_name );
            if( wire_name == CLKNAME )
                new_wire( wire_name, m, 0 );
            else
                new_wire( wire_name, m, wire_type );
            printf ("%s\n",pch);
            pch = strtok (NULL, " ,;");
        }
    }
    else if( find_l != string::npos && find_m != string::npos && find_r != string::npos  )
    {
        int a =  atoi( s.substr( find_l + 1, find_m - find_l - 1 ).c_str() );
        int b =  atoi( s.substr( find_m + 1, find_r - find_m - 1 ).c_str() );
        cout << a << " " << b<< endl;
        int low  = ( a < b )? a : b ;
        int high = ( a > b )? a : b ;

        
        strcpy( str, s.substr( find_r + 1 ).c_str());
        pch = strtok ( str, " ,;");
        while (pch != NULL)
        {
            for( int i = low; i <= high; i++ )
            {
                string wire_name(pch);
                string index_s = to_string(i);
                wire_name.append("[");
                wire_name.append(index_s);
                wire_name.append("]");
                //Wire* wire = new Wire( wire_name );
                new_wire( wire_name, m, wire_type );
                cout << wire_name << endl;
            }
            pch = strtok (NULL, " ,;");
        }
    } 
     
    delete str;
}

void new_wire( string s, map< string, Wire* >& m, int wire_type )
{
    m[ s ] = new Wire(s, wire_type);
}

void build_gate( string s, map< string, Gate* >& map_gate, map< string, Wire* >& map_wire)
{
    char* pch;
    char* str = new char[ s.size() + 1 ];
    int counter = 0;
    string gate_name;
    string gate_type;
    //vector< string > port_list;
    //vector< Wire* > wire_list;


    //   gate name & type 
    strcpy( str, s.c_str());
    pch = strtok ( str, " ,;().");
    while (pch != NULL)
    {
    
        if( counter == 0 )
            gate_type.assign( pch );
        else if ( counter == 1 )
            gate_name.assign( pch );
        else 
            break;
        pch = strtok (NULL, " ,;().");
        counter++;
    }

    Gate* curgate = new Gate( gate_name, gate_type );
    map_gate[ gate_name ] = curgate;


    // gate inputs & outputs
    string port_string = s.substr(s.find("(")); 

    string::iterator it = remove( port_string.begin(), port_string.end(), ' ');
    port_string.erase( it, port_string.end() );
    strcpy( str, port_string.c_str());
    pch = strtok ( str, " ,;().");
    counter = 0;
    while (pch != NULL)
    {
        if ( counter % 2 == 0 )
        {
            string port_name( pch );
            curgate -> add_port_list( port_name );
        }
        else 
        {
            string wire_name( pch );
            //wire_list.push_back( map_wire[ wire_name] );
            //map<string ,Wire*>::iterator it = map_wire.find( wire_name );
            //if( it == map_wire.end() )
            //    cout << "SHIT\n";
            curgate -> add_wire_list( map_wire[ wire_name] );
        }
        //printf ("%s ",pch);
        pch = strtok (NULL, " ,;().");
        counter++;
    }
    //cout << endl;


}
void gate_add_fanin( Gate* g, Wire* w )
{
    g -> add_fanin_wire( w );
    w -> add_fanout_gate( g );
}
void gate_add_fanout( Gate* g, Wire* w )
{
    g -> add_fanout_wire( w );
    w -> add_fanin_gate( g );
}

void input_output_DFF( map< string, Gate* >& map_gate, map< string, Wire*> & map_wire )
{
    Gate* curgate;
    Wire* newwire;
    Wire* curwire;
    int counter = 0;
    vector< string > curwire_name_list;
    vector< Wire*  > curwire_list;

    for ( map<string ,Wire*>::iterator it= map_wire.begin(); it!= map_wire.end(); ++it)
    {
        curwire = it -> second;
        if( curwire -> get_wire_type() ==  1 )
        {
            string gate_name = "input_dff_";
            string index_s = to_string( counter );
            gate_name.append(index_s);
            string wire_name =  curwire -> get_name();
            newwire = new Wire( wire_name ,0);

            Wire* clkwire = map_wire[ CLKNAME ]; // clock name 

            string curwire_name = curwire -> set_name();
            cout << "input eliminate: " << wire_name << endl;

            //map_wire[ curwire_name ] = curwire;
            curwire_name_list.push_back( curwire_name );
            curwire_list.push_back( curwire );

            vector< string > curwire_name_list;
            vector< Wire*  > curwire_list;
            map_wire[ wire_name ]    = newwire;

            add_DFF_gate( map_gate, gate_name, newwire, clkwire, curwire ); 

        }
        
        if( curwire -> get_wire_type() ==  2 )
        {

            string gate_name = "output_dff_";
            string index_s = to_string( counter );
            gate_name.append(index_s);
            string wire_name =  curwire -> get_name();
            newwire = new Wire( wire_name ,0);
        
            Wire* clkwire = map_wire[ CLKNAME ]; // clock name 
            
            string curwire_name = curwire -> set_name();
            cout << "output eliminate: " << wire_name << endl;
            //map_wire[ curwire_name ] = curwire;
            curwire_name_list.push_back( curwire_name );
            curwire_list.push_back( curwire );
            map_wire[ wire_name ]    = newwire;
             

            add_DFF_gate( map_gate, gate_name, curwire, clkwire, newwire ); 
        }
        
        counter++;
    }

    for( size_t i = 0; i < curwire_name_list.size(); i++ )
        map_wire[ curwire_name_list[i] ] = curwire_list[i];
}

void print_gate( map< string, Gate* >& map_gate )
{
    Gate* curgate;
    for ( map<string ,Gate*>::iterator it= map_gate.begin(); it!= map_gate.end(); ++it)
    {
        curgate = it -> second;
        cout << curgate -> get_type() << " " << curgate -> get_name() << " (";
        
        for( size_t i = 0; i < curgate -> port_list_size(); i++ )
        {
            if( i != 0 )
                cout << ", ";
            cout << "." << curgate -> get_port_list(i) << "(";
            cout << curgate -> get_wire_list(i) -> get_name() << ")"; 
        }
        
        cout << ");\n";
        
    }


}

void gate_wire_connection( map< string, Gate* >& map_gate, 
                           map< string, Wire* >& map_wire )
{
    Gate* curgate;
    Wire* curwire;
    
    for ( map<string ,Gate*>::iterator it= map_gate.begin(); it!= map_gate.end(); ++it)
    {
        curgate = it -> second;
        curgate -> fanin_wire_clear();
        curgate -> fanout_wire_clear();
    }
    for ( map<string ,Wire*>::iterator it= map_wire.begin(); it!= map_wire.end(); ++it)
    {
        curwire = it -> second;
        curwire -> fanin_gate_clear();
        curwire -> fanout_gate_clear();
    }


    for ( map<string ,Gate*>::iterator it= map_gate.begin(); it!= map_gate.end(); ++it)
    {
        curgate = it -> second;
        size_t find_DFF = curgate -> get_type().find("DFF");
        size_t find_ADD = curgate -> get_type().find("ADD");

        if( find_DFF != string::npos )
        {
            for( size_t i = 0; i < curgate -> port_list_size(); i++ )
            {
                if( curgate -> get_port_list(i) != "Q" )
                    curgate -> gate_add_fanin( i );
                else
                    curgate -> gate_add_fanout( i );
            }
        }
        else if ( find_ADD != string::npos )
        {
            //for( size_t i = 0; i < port_list.size(); i++ )
            for( size_t i = 0; i < curgate -> port_list_size(); i++ )
            {
                if( curgate -> get_port_list(i) != "CO" 
                 && curgate -> get_port_list(i) != "S" )
                    curgate -> gate_add_fanin( i );
                    //gate_add_fanin( curgate, wire_list[ i ] );
                else
                    //gate_add_fanout( curgate, wire_list[ i ] );
                    curgate -> gate_add_fanout( i );
            }
        }
        else
        {
            //for( size_t i = 0; i < port_list.size(); i++ )
            for( size_t i = 0; i < curgate -> port_list_size(); i++ )
            {
                //if( port_list[i] != "Y" )
                if( curgate -> get_port_list(i) != "Y" )
                    curgate -> gate_add_fanin( i );
                    //gate_add_fanin( curgate, wire_list[ i ] );
                else
                    //gate_add_fanout( curgate, wire_list[ i ] );
                    curgate -> gate_add_fanout( i );
            }
        }
    }
}


void DFF_modification( map< string, Gate* >& map_gate, map< string, Wire* >& map_wire )
{
    Gate* curgate;

    Gate* gate_AND1;
    Gate* gate_AND2;
    Gate* gate_OR;
    Gate* gate_DFF;
    Gate* gate_INV;
    
    string gate_AND1_name;
    string gate_AND2_name;
    string gate_OR_name;
    string gate_DFF_name;
    string gate_INV_name;

    Wire* wire_D;
    Wire* wire_E;
    Wire* wire_CK;
    Wire* wire_Q;
    Wire* wire_AND1;
    Wire* wire_AND2;
    Wire* wire_OR;
    Wire* wire_INV;
    
    string wire_AND1_name;
    string wire_AND2_name;
    string wire_OR_name;
    string wire_INV_name;

    string gate_name;

    vector< string > erase_list;
    for ( map<string ,Gate*>::iterator it= map_gate.begin(); it!= map_gate.end(); ++it)
    {
        curgate = it -> second;
        gate_name = curgate -> get_name();
        size_t find = curgate -> get_type().find( "EDFF" );
        if( find == string::npos )
            continue;
        wire_D  = curgate -> get_wire_list( 0 ); 
        wire_E  = curgate -> get_wire_list( 1 ); 
        wire_CK = curgate -> get_wire_list( 2 ); 
        wire_Q  = curgate -> get_wire_list( 3 );
    
        gate_AND1_name = gate_name; 
        gate_AND2_name = gate_name;
        gate_OR_name   = gate_name;
        gate_DFF_name  = gate_name;
        gate_INV_name  = gate_name;

        gate_AND1_name.append("_AND1"); 
        gate_AND2_name.append("_AND2");
        gate_OR_name.append("_OR");
        gate_DFF_name.append("_DFF");
        gate_INV_name.append("_INV");
        
        wire_AND1_name = gate_name; 
        wire_AND2_name = gate_name;
        wire_OR_name   = gate_name;
        wire_INV_name  = gate_name;

        wire_AND1_name.append("_AND1_w"); 
        wire_AND2_name.append("_AND2_w");
        wire_OR_name.append("_OR_w");
        wire_INV_name.append("_INV_w");
 
        wire_INV  = new Wire( wire_INV_name,  0 );
        wire_OR   = new Wire( wire_OR_name,   0 );
        wire_AND1 = new Wire( wire_AND1_name, 0 );
        wire_AND2 = new Wire( wire_AND2_name, 0 );

        map_wire[ wire_INV_name  ]= wire_INV;
        map_wire[ wire_OR_name   ]= wire_OR;
        map_wire[ wire_AND1_name ]= wire_AND1;
        map_wire[ wire_AND2_name ]= wire_AND2;
        
        
        add_AND_gate( map_gate, gate_AND1_name, wire_D, wire_E, wire_AND1 );
        add_INV_gate( map_gate, gate_INV_name, wire_E, wire_INV );
        add_AND_gate( map_gate, gate_AND2_name, wire_INV, wire_Q, wire_AND2 );
        add_OR_gate ( map_gate, gate_OR_name, wire_AND1, wire_AND2, wire_OR );
        add_DFF_gate( map_gate, gate_DFF_name, wire_OR, wire_CK, wire_Q );


        erase_list.push_back( gate_name );
    }

    for( size_t i = 0; i < erase_list.size(); i++ )
        map_gate.erase( erase_list[i] );
}


void add_AND_gate( map< string, Gate* >& map_gate, string gate_name, 
                   Wire* wire_A, Wire* wire_B, Wire* wire_Y )
{
    string gate_type = "AND2X1";
    Gate* curgate = new Gate( gate_name, gate_type );
    curgate -> add_port_list("A");
    curgate -> add_port_list("B");
    curgate -> add_port_list("Y");
    curgate -> add_wire_list( wire_A );
    curgate -> add_wire_list( wire_B );
    curgate -> add_wire_list( wire_Y );
    map_gate[ gate_name ] = curgate;
}

void add_OR_gate( map< string, Gate* >& map_gate, string gate_name, 
                   Wire* wire_A, Wire* wire_B, Wire* wire_Y )
{
    string gate_type =  "OR2X1" ;
    Gate* curgate = new Gate( gate_name, gate_type );
    curgate -> add_port_list("A");
    curgate -> add_port_list("B");
    curgate -> add_port_list("Y");
    curgate -> add_wire_list( wire_A );
    curgate -> add_wire_list( wire_B );
    curgate -> add_wire_list( wire_Y );
    map_gate[ gate_name ] = curgate;
}

void add_DFF_gate( map< string, Gate* >& map_gate, string gate_name, 
                   Wire* wire_D, Wire* wire_CK, Wire* wire_Q )
{
    string gate_type = "DFFQX1" ;
    Gate* curgate = new Gate( gate_name, gate_type );
    curgate -> add_port_list("D");
    curgate -> add_port_list("CK");
    curgate -> add_port_list("Q");
    curgate -> add_wire_list( wire_D );
    curgate -> add_wire_list( wire_CK );
    curgate -> add_wire_list( wire_Q );
    map_gate[ gate_name ] = curgate;
}

void add_INV_gate( map< string, Gate* >& map_gate, string gate_name, 
                   Wire* wire_A, Wire* wire_Y )
{
    string gate_type =  "INVX1" ;
    Gate* curgate = new Gate( gate_name, gate_type );
    curgate -> add_port_list("A");
    curgate -> add_port_list("Y");
    curgate -> add_wire_list( wire_A );
    curgate -> add_wire_list( wire_Y );
    map_gate[ gate_name ] = curgate;
}
bool isDFF( Gate* curgate )
{
    size_t find = curgate -> get_type().find( "DFFQ" );
    if( find == string::npos )
        return false;
    else
        return true;
}

Gate* DFS_next_gate( Gate* curgate, const int& flag_counter )
{
    Gate* tempgate;
    Wire* tempwire;
    for( size_t i = 0; i < curgate -> fanout_wire_size(); i++ )
    {
        tempwire = curgate -> get_fanout_wire( i );
        for( size_t j = 0; j < tempwire -> fanout_gate_size(); j++ )
        {
            tempgate = tempwire -> get_fanout_gate( j );
            if( tempgate -> get_flag() != flag_counter )
                return tempgate;
        }
    }

    return NULL;
}

void initial_queue( Gate* curgate, const int& flag_counter, queue< Gate* >& Q )
{
    Gate* tempgate;
    Wire* tempwire;
    for( size_t i = 0; i < curgate -> fanout_wire_size(); i++ )
    {
        tempwire = curgate -> get_fanout_wire( i );
        for( size_t j = 0; j < tempwire -> fanout_gate_size(); j++ )
        {
            tempgate = tempwire -> get_fanout_gate( j );
            tempgate -> set_flag( flag_counter );
            Q.push( tempgate );
        }
    }
}


void DFS_DFF_connection( map< string, Gate* >& map_gate )
{
    Gate* curgate;
    Gate* tempgate;
    Gate* nextgate;

    int flag_counter = 0;
    queue < Gate* > Q;
    vector< Gate* > next_DFF;
    
    for ( map<string ,Gate*>::iterator it= map_gate.begin(); it!= map_gate.end(); ++it)
    {
        
        curgate = it -> second;
        if( !isDFF( curgate ) )
            continue;
        curgate -> fanin_dff_clear();
        curgate -> fanout_dff_clear();
    }
    
    

    for ( map<string ,Gate*>::iterator it= map_gate.begin(); it!= map_gate.end(); ++it)
    {
        curgate = it -> second;
        if( !isDFF( curgate ) )
            continue;

        //cout << curgate -> get_name() << ":" << endl; 
        next_DFF.clear();
        initial_queue( curgate, flag_counter, Q );
        while( !Q.empty() )
        {
            tempgate = Q.front();
            //Q.pop();
            //cout << tempgate -> get_name() << " ";
            if( isDFF( tempgate ) )
            {
                next_DFF.push_back( tempgate );
                //cout << tempgate -> get_name() << " ";
                Q.pop();
                continue;
            }
            
            nextgate = DFS_next_gate( tempgate, flag_counter );

            if( nextgate == NULL )
            {
                Q.pop();
                continue;
            }
           
            nextgate -> set_flag( flag_counter );
            //cout << nextgate -> get_name() << " ";
            Q.push( nextgate );
        }
        //cout << endl;


        DFF_connection( curgate, next_DFF );

        flag_counter++;
    }
}

void DFF_connection( Gate* curgate, vector< Gate* >& next_DFF )
{
    for( size_t i = 0; i < next_DFF.size(); i++ )
    {
        curgate     -> add_fanout_dff( next_DFF[i] );
        next_DFF[i] -> add_fanin_dff( curgate );
    }

}

void update_DFF_level( Gate* curgate, int& Maxlevel )
{
    int curlevel = curgate -> get_level();

    if( curlevel != -1 )
    {
        Maxlevel = ( Maxlevel > curlevel )? Maxlevel : curlevel;
        return;
    }

    int templevel;
    curlevel = -1;
    for( size_t i = 0; i < curgate -> fanin_dff_size(); i++ )
    {
        templevel = curgate -> get_fanin_dff( i ) -> get_level();
        
        if( templevel == -1 )
            return;
        curlevel = ( curlevel > templevel )? curlevel : templevel; 
    }
}

void DFF_levelization( map< string, Gate* >& map_gate )
{
    Gate* curgate;
    vector< Gate* > input_DFF;
    vector< Gate* > rest_DFF;

    for ( map<string ,Gate*>::iterator it= map_gate.begin(); it!= map_gate.end(); ++it)
    {
        curgate = it -> second;
        if( !isDFF( curgate ) )
            continue;

        if( curgate -> get_fanout_wire(0) -> get_wire_type() == 1 )
            input_DFF.push_back( curgate );
        else
            rest_DFF.push_back( curgate );

    }

    /*
    cout << "INPUT DFF: \n";
    for( size_t i = 0; i < input_DFF.size(); i++ )
        cout << input_DFF[i] -> get_name() << " ";
    cout << endl;
    
    cout << "REST DFF: \n";
    for( size_t i = 0; i < rest_DFF.size(); i++ )
        cout << rest_DFF[i] -> get_name() << " ";
    cout << endl;
    */

    for( size_t i = 0; i < input_DFF.size(); i++ )
        input_DFF[i] -> set_level( 1 );
    
}

void fix_cycle_one_level( Gate* curgate, map< string, Wire* >& map_wire,
                                         map< string, Gate* >& map_gate )
{
    Wire* origin_D  = curgate -> get_wire_list(0);
    Wire* origin_CK = curgate -> get_wire_list(1);
    Wire* origin_Q  = curgate -> get_wire_list(2);
    string wire_name_1 = curgate -> get_name();
    string wire_name_2 = curgate -> get_name();
    string gate_name_1 = curgate -> get_name();
    string gate_name_2 = curgate -> get_name();
    wire_name_1.append("_cycle1_1_w");
    wire_name_2.append("_cycle1_2_w");
    gate_name_1.append("_cycle1_1");
    gate_name_2.append("_cycle1_2");

    Wire* new_net_1 = new Wire( wire_name_1, 0 );
    Wire* new_net_2 = new Wire( wire_name_2, 0 );

    
    map_wire[ wire_name_1 ] = new_net_1;
    map_wire[ wire_name_2 ] = new_net_2;
    curgate -> set_wire_list( 2, new_net_1 );
    add_DFF_gate( map_gate, gate_name_1, new_net_1, origin_CK, new_net_2 );
    add_DFF_gate( map_gate, gate_name_2, new_net_2, origin_CK, origin_Q );
}

void fix_cycle_two_level( Gate* curgate, map< string, Wire* >& map_wire,
                                         map< string, Gate* >& map_gate )
{
    Wire* origin_D  = curgate -> get_wire_list(0);
    Wire* origin_CK = curgate -> get_wire_list(1);
    Wire* origin_Q  = curgate -> get_wire_list(2);
    string wire_name_1 = curgate -> get_name();
    string gate_name_1 = curgate -> get_name();
    wire_name_1.append("_cycle2_1_w");
    gate_name_1.append("_cycle2_1");

    Wire* new_net_1 = new Wire( wire_name_1, 0 );

    
    map_wire[ wire_name_1 ] = new_net_1;
    curgate -> set_wire_list( 2, new_net_1 );
    add_DFF_gate( map_gate, gate_name_1, new_net_1, origin_CK, origin_Q );
}

void Deadlock_elimination( map< string, Gate* > & map_gate, 
                           map< string, Wire* > & map_wire )
{

    Gate* curgate;
    Gate* tempgate;
    vector< Gate* > cycle_one_level;
    vector< Gate* > cycle_two_level;

    cout << "ONE LEVEL CYCLE:\n";
    for ( map<string ,Gate*>::iterator it= map_gate.begin(); it!= map_gate.end(); ++it)
    {
        curgate = it -> second;
        if( !isDFF( curgate ) )
            continue;
        for( size_t i = 0; i < curgate -> fanin_dff_size(); i++ )
        {
            if( curgate == curgate -> get_fanin_dff(i) )
            {
                cycle_one_level.push_back( curgate );
                break;
            }
        }
    }
   

    for( size_t i = 0; i < cycle_one_level.size(); ++i )
    {
        //cout << cycle_one_level[i] -> get_name() << " ";
        curgate = cycle_one_level[i];
        fix_cycle_one_level( curgate, map_wire, map_gate );
    }

    if( !cycle_one_level.empty() )
    {
        gate_wire_connection( map_gate, map_wire );
        DFS_DFF_connection( map_gate );
    }



    cout << "TWO LEVEL CYCLE:\n";
    for ( map<string ,Gate*>::iterator it= map_gate.begin(); it!= map_gate.end(); ++it)
    {
        curgate = it -> second;
        if( !isDFF( curgate ) )
            continue;
        for( size_t i = 0; i < curgate -> fanin_dff_size(); ++i )
        {
            tempgate = curgate -> get_fanin_dff( i );
            for( size_t j = 0; j < tempgate -> fanin_dff_size(); ++j )
            {
                if( curgate == tempgate -> get_fanin_dff(j) )
                {
                    Gate* pushgate;
                    if( curgate -> get_name() > tempgate -> get_name() )
                        pushgate = curgate;
                    else
                        pushgate = tempgate;

                    bool appear = false;
                    for( size_t k = 0; k < cycle_two_level.size(); ++k )
                        if( cycle_two_level[k] == pushgate )
                        {
                            appear = true;
                            break;
                        }

                    if( !appear )
                    {
                        cout << "push: " << pushgate -> get_name() << endl;
                        cycle_two_level.push_back( pushgate );
                    }
                    break;
                }
            }
        }
    }

    for( size_t i = 0; i < cycle_two_level.size(); ++i )
    {
        //cout << cycle_one_level[i] -> get_name() << " ";
        curgate = cycle_two_level[i];
        fix_cycle_two_level( curgate, map_wire, map_gate );
    }
    
    if( !cycle_two_level.empty() )
    {
        gate_wire_connection( map_gate, map_wire );
        DFS_DFF_connection( map_gate );
    }




}



