#include "DG.h"
#include "Cycle_list.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

bool isDFF( Gate* curgate )
{
    size_t find = curgate -> get_type().find( "DFFQ" );
    if( find == string::npos )
        return false;
    else
        return true;
}



string fix_wire_name( string s )
{
    char* pch;
    char* str = new char[ s.size() + 1 ];
    string name;
    
    strcpy( str, s.c_str());
    pch = strtok ( str, "[]");
    while (pch != NULL)
    {
        string wire_name(pch);
        name.append( wire_name );
        pch = strtok (NULL, "[]");
    }

    delete str; 
    return name;
}

string fix_port_name( Wire* w )
{
    
    if( w -> addition )
        return fix_wire_name( w -> get_name() );
    else
        return w -> get_name();
}

string Wire::get_name_v()
{
    size_t find = name.find("[");
    string name_v;
    if( find == string::npos )
    {
        name_v = name;
        if( wire_type == 1 )
            name_v.append("_i");
        if( wire_type == 2 )
            name_v.append("_o");
    }
    else
    {
        name_v = name.substr(0, find );
        if( wire_type == 1 )
            name_v.append("_i");
        if( wire_type == 2 )
            name_v.append("_o");
        name_v.append( name.substr(find));
    }

    return name_v;

}

string Wire::get_name(int i )
{
    string name_fix;
    if( addition )
        name_fix = fix_wire_name( name );
    else
        name_fix = name;

    size_t find = name.find("[");
    string name_v;
    string index_s =  to_string(i);
    if( find == string::npos )
    {
        name_v = name_fix;
        name_v.append("_");
        name_v.append(index_s);
    }
    else
    {
        name_v = name_fix.substr(0, find );
        name_v.append("_");
        name_v.append(index_s);
        name_v.append( name_fix.substr(find));
    }

    return name_v;

}

string Wire::set_name()
{
    size_t find = name.find("[");
    string name_v;
    if( find == string::npos )
    {
        name_v = name;
        if( wire_type == 1 )
            name_v.append("_i");
        if( wire_type == 2 )
            name_v.append("_o");
    }
    else
    {
        name_v = name.substr(0, find );
        if( wire_type == 1 )
            name_v.append("_i");
        if( wire_type == 2 )
            name_v.append("_o");
        name_v.append( name.substr(find));
    }
    name = name_v;
    return name;
}


void Gate::gate_add_fanin( int i )
{
    Wire* w = wire_list[i];
    this -> add_fanin_wire ( w );
    w    -> add_fanout_gate( this );
}

void Gate::gate_add_fanout( int i )
{
    Wire* w = wire_list[i];
    this -> add_fanout_wire( w );
    w    -> add_fanin_gate ( this );
}






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
    CLKNAME = "clk";
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



/// 

void DGraph::build_wire( string s, int& wire_type)
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
                new_wire( wire_name, 0 );
            else
                new_wire( wire_name, wire_type );
            //printf ("%s\n",pch);
            pch = strtok (NULL, " ,;");
        }
    }
    else if( find_l != string::npos && find_m != string::npos && find_r != string::npos  )
    {
        int a =  atoi( s.substr( find_l + 1, find_m - find_l - 1 ).c_str() );
        int b =  atoi( s.substr( find_m + 1, find_r - find_m - 1 ).c_str() );
        //cout << a << " " << b<< endl;
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
                new_wire( wire_name, wire_type );
                //cout << wire_name << endl;
            }
            pch = strtok (NULL, " ,;");
        }
    } 
     
    delete str;
}

void DGraph::new_wire( string s, int wire_type )
{
    map_wire[ s ] = new Wire(s, wire_type);
}

void DGraph::build_gate( string s )
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

    delete str;
}
void DGraph::gate_add_fanin( Gate* g, Wire* w )
{
    g -> add_fanin_wire( w );
    w -> add_fanout_gate( g );
}
void DGraph::gate_add_fanout( Gate* g, Wire* w )
{
    g -> add_fanout_wire( w );
    w -> add_fanin_gate( g );
}

void DGraph::input_output_DFF()
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
            //cout << "input eliminate: " << wire_name << endl;

            //map_wire[ curwire_name ] = curwire;
            curwire_name_list.push_back( curwire_name );
            curwire_list.push_back( curwire );

            vector< string > curwire_name_list;
            vector< Wire*  > curwire_list;
            map_wire[ wire_name ]    = newwire;
            
            add_DFF_gate( gate_name, newwire, clkwire, curwire ); 

            addition_wire.push_back( curwire_name );
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
            //cout << "output eliminate: " << wire_name << endl;
            //map_wire[ curwire_name ] = curwire;
            curwire_name_list.push_back( curwire_name );
            curwire_list.push_back( curwire );
            map_wire[ wire_name ]    = newwire;
             

            add_DFF_gate( gate_name, curwire, clkwire, newwire ); 
            addition_wire.push_back( curwire_name );
            
        }
        
        counter++;
    }

    for( size_t i = 0; i < curwire_name_list.size(); i++ )
        map_wire[ curwire_name_list[i] ] = curwire_list[i];
}

void DGraph::print_module_declaration()
{
    char* pch;
    char* str = new char[ module_declaration.size() + 1 ];
    int counter = 0;
    string gate_name;
    string gate_type;
    //vector< string > port_list;
    //vector< Wire* > wire_list;
    vector< string > port_name;

    //   gate name & type 
    strcpy( str, module_declaration.c_str());
    pch = strtok ( str, " ,;().");
    while (pch != NULL)
    {
    
        if( counter == 0 )
            gate_type.assign( pch );
        else if ( counter == 1 )
            gate_name.assign( pch );
        else 
        {
            string p(pch);

            port_name.push_back( p );
        }
        pch = strtok (NULL, " ,;().");
        counter++;
    }

    cout << gate_type << " " << gate_name << "( async_rst";
    for( size_t i = 0; i < port_name.size(); ++i )
    {   
        if( port_name[i] == CLKNAME )
            continue;
        cout << ", " << port_name[i] << "_0, " << port_name[i] << "_1";
    }
    cout << ", ACK_IN, ACK_OUT);\n";
    delete str;
}


void DGraph::print_input_declaration()
{
    for( size_t i = 0; i < input_declaration.size(); ++i )
    {
        size_t find = input_declaration[i].find("]");
        string s;
        string range;
        if( find == string::npos )
        {
            s = input_declaration[i];
            range = "";
        }
        else
        {
            s = input_declaration[i].substr( find + 1 );
            range = input_declaration[i].substr( 0, find + 1 );
        }

        char* str = new char[ input_declaration[i].size() + 1 ];
        char* pch;
        vector< string > wire_name;
        strcpy( str, s.c_str());
        pch = strtok ( str, " ,;().");
        while (pch != NULL)
        {
            string p(pch);
            wire_name.push_back( p );
            pch = strtok (NULL, " ,;().");
        }
        cout << "    input " << range << " ";
        int counter = 0;
        for( size_t i = 0; i < wire_name.size(); ++i )
        {   
            if( wire_name[i] == CLKNAME )
                continue;

            if( counter != 0 )
                cout << ",";
            cout << wire_name[i] << "_0, " << wire_name[i] << "_1";
            ++counter;
        }
        cout << ";\n";
        delete str;
    }
    cout << "    input  async_rst, ACK_IN;\n";
}

void DGraph::print_output_declaration()
{
    for( size_t i = 0; i < output_declaration.size(); ++i )
    {
        size_t find = output_declaration[i].find("]");
        string s;
        string range;
        if( find == string::npos )
        {
            s = output_declaration[i];
            range = "";
        }
        else
        {
            s = output_declaration[i].substr( find + 1 );
            range = output_declaration[i].substr( 0, find + 1 );
        }

        char* str = new char[ output_declaration[i].size() + 1 ];
        char* pch;
        vector< string > wire_name;
        strcpy( str, s.c_str());
        pch = strtok ( str, " ,;().");
        while (pch != NULL)
        {
            string p(pch);
            wire_name.push_back( p );
            pch = strtok (NULL, " ,;().");
        }
        cout << "    output " << range << " ";
        int counter = 0;
        for( size_t i = 0; i < wire_name.size(); ++i )
        {   
            if( wire_name[i] == CLKNAME )
                continue;

            if( counter != 0 )
                cout << ",";
            cout << wire_name[i] << "_0, " << wire_name[i] << "_1";
            ++counter;
        }
        cout << ";\n";
        delete str;
    }
    cout << "    output  ACK_OUT;\n";
}

void DGraph::print_wire_declaration()
{
    for( size_t i = 0; i < wire_declaration.size(); ++i )
    {
        size_t find = wire_declaration[i].find("]");
        string s;
        string range;
        if( find == string::npos )
        {
            s = wire_declaration[i];
            range = "";
        }
        else
        {
            s = wire_declaration[i].substr( find + 1 );
            range = wire_declaration[i].substr( 0, find + 1 );
        }

        char* str = new char[ wire_declaration[i].size() + 1 ];
        char* pch;
        vector< string > wire_name;
        strcpy( str, s.c_str());
        pch = strtok ( str, " ,;().");
        while (pch != NULL)
        {
            string p(pch);
            wire_name.push_back( p );
            pch = strtok (NULL, " ,;().");
        }
        cout << "    wire " << range << " ";
        int counter = 0;
        for( size_t i = 0; i < wire_name.size(); ++i )
        {   
            if( wire_name[i] == CLKNAME )
                continue;

            if( counter != 0 )
                cout << ",";
            cout << wire_name[i] << "_0, " << wire_name[i] << "_1";
            ++counter;
        }
        cout << ";\n";
        delete str;
    }
    
    cout << "    wire ";
    for( size_t i = 0; i < addition_wire.size(); ++i )
    {
        if( i != 0 )
            cout << ", ";
        cout << fix_wire_name( addition_wire[i] )<< "_0, " << fix_wire_name( addition_wire[i] ) << "_1";
        map_wire[ addition_wire[i] ] -> addition = true;
    }
    cout << ";\n";
    
    cout << "    wire ";
    for( size_t i = 0; i < ack_wire_list.size(); ++i )
    {
        if( i != 0 )
            cout << ", ";
        cout << fix_wire_name( ack_wire_list[i] -> get_name() );
        ack_wire_list[i] -> addition = true;
    }
    cout << ";\n";
    
}


void DGraph::print_Verilog()
{
    
    print_module_declaration();
    print_input_declaration();
    print_output_declaration();
    print_wire_declaration();
    //cout << input_declaration << endl;
    //cout << output_declaration << endl;
    //cout << wire_declaration << endl;
    print_gate();
    cout << "endmodule" << endl;
    print_module();


}

void DGraph::print_module()
{
    Module* curmodule;
    for ( map<string ,Module*>::iterator it= map_module.begin(); it!= map_module.end(); ++it)
    {
        curmodule = it -> second;
        cout << curmodule -> get_content();
        cout << endl;
    }

}


void DGraph::print_gate()
{
    Gate* curgate;
    for ( map<string ,Gate*>::iterator it= map_gate.begin(); it!= map_gate.end(); ++it)
    {
        curgate = it -> second;
        if( !isDFF( curgate ) )
        {
            cout << "    " << curgate -> get_type() << "_async " << fix_wire_name( curgate -> get_name() )<< " (";
            for( size_t i = 0; i < curgate -> port_list_size(); i++ )
            {
                if( i != 0 )
                    cout << ", ";
                cout << "." << curgate -> get_port_list(i) << "_0(";
                cout << curgate -> get_wire_list(i) -> get_name(0) << ")"; 

                cout << ", ";
                cout << "." << curgate -> get_port_list(i) << "_1(";
                cout << curgate -> get_wire_list(i) -> get_name(1) << ")"; 
            }
            cout << ");\n";
        }
        else
        {
            if( curgate -> get_fvs() )
                cout << "    NCL_register_rst " << fix_wire_name( curgate -> get_name() )<< " (";
            else
                cout << "    NCL_register " << fix_wire_name( curgate -> get_name() )<< " (";

            cout << ".A_0(";
            cout << curgate -> get_wire_list(0) -> get_name(0) << ")"; 

            cout << " ,.A_1(";
            cout << curgate -> get_wire_list(0) -> get_name(1) << ")"; 

            cout << " ,.ack_in(";
            cout << curgate -> get_wire_list(1) -> get_name() << ")"; 

            cout << " ,.Y_0(";
            cout << curgate -> get_wire_list(2) -> get_name(0) << ")"; 

            cout << " ,.Y_1(";
            cout << curgate -> get_wire_list(2) -> get_name(1) << ")"; 
            if( curgate -> get_fvs() )
                cout << " ,.rst(rst)";
    
            cout << ");\n";
        }        
    }

    for( size_t i = 0; i < ack_gate_list.size(); ++i )
    {
        curgate = ack_gate_list[i];
        cout << "    " << curgate -> get_type() << "_async " << fix_wire_name( curgate -> get_name() )<< " (";
        for( size_t i = 0; i < curgate -> port_list_size(); i++ )
        {
            if( i == 0 )
            {
                cout << ".Y(";
                cout << fix_wire_name( curgate -> get_wire_list(i) -> get_name() ) << ")";
            }
            else
            {
                cout << ",." << curgate -> get_port_list(i) << "_0(";
                cout << curgate -> get_wire_list(i) -> get_name(0) << ")"; 
                cout << ",." << curgate -> get_port_list(i) << "_1(";
                cout << curgate -> get_wire_list(i) -> get_name(1) << ")"; 
            }
        }
        cout << ");\n";
    }
    /*
    for ( map<string ,Gate*>::iterator it= map_gate.begin(); it!= map_gate.end(); ++it)
    {
        curgate = it -> second;
        if( !isDFF( curgate ) ) 
            continue;
        
        cout << curgate -> get_type() << " " << curgate -> get_name() << endl;

        cout << "FANIN:\n";
        for( size_t i = 0; i < curgate -> fanin_dff_size(); i++ )
            cout << curgate -> get_fanin_dff(i) -> get_name() << " ";
        cout << endl;

        cout << "FANOUT:\n";
        for( size_t i = 0; i < curgate -> fanout_dff_size(); i++ )
            cout << curgate -> get_fanout_dff(i) -> get_name() << " ";
        cout << endl;
    }
    */
}

void DGraph::gate_wire_connection()
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


void DGraph::DFF_modification()
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

        addition_wire.push_back( wire_INV_name );
        addition_wire.push_back( wire_OR_name );
        addition_wire.push_back( wire_AND1_name );
        addition_wire.push_back( wire_AND2_name );
        
        map_wire[ wire_INV_name  ]= wire_INV;
        map_wire[ wire_OR_name   ]= wire_OR;
        map_wire[ wire_AND1_name ]= wire_AND1;
        map_wire[ wire_AND2_name ]= wire_AND2;
        
        
        add_AND_gate( gate_AND1_name, wire_D, wire_E, wire_AND1 );
        add_INV_gate( gate_INV_name, wire_E, wire_INV );
        add_AND_gate( gate_AND2_name, wire_INV, wire_Q, wire_AND2 );
        add_OR_gate ( gate_OR_name, wire_AND1, wire_AND2, wire_OR );
        add_DFF_gate( gate_DFF_name, wire_OR, wire_CK, wire_Q );


        erase_list.push_back( gate_name );
    }

    for( size_t i = 0; i < erase_list.size(); i++ )
        map_gate.erase( erase_list[i] );
}


void DGraph::add_AND_gate( string gate_name, Wire* wire_A, Wire* wire_B, Wire* wire_Y )
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

void DGraph::add_OR_gate( string gate_name, Wire* wire_A, Wire* wire_B, Wire* wire_Y )
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

void DGraph::add_DFF_gate( string gate_name, Wire* wire_D, Wire* wire_CK, Wire* wire_Q )
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

void DGraph::add_INV_gate( string gate_name, Wire* wire_A, Wire* wire_Y )
{
    string gate_type =  "INVX1" ;
    Gate* curgate = new Gate( gate_name, gate_type );
    curgate -> add_port_list("A");
    curgate -> add_port_list("Y");
    curgate -> add_wire_list( wire_A );
    curgate -> add_wire_list( wire_Y );
    map_gate[ gate_name ] = curgate;
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


void DGraph::DFS_DFF_connection()
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

void DGraph::DFF_connection( Gate* curgate, vector< Gate* >& next_DFF )
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

void DGraph::DFF_levelization()
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

void DGraph::fix_cycle_one_level( Gate* curgate )
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

    
    addition_wire.push_back( wire_name_1 );
    addition_wire.push_back( wire_name_2 );

    
    map_wire[ wire_name_1 ] = new_net_1;
    map_wire[ wire_name_2 ] = new_net_2;
    curgate -> set_wire_list( 2, new_net_1 );
    add_DFF_gate( gate_name_1, new_net_1, origin_CK, new_net_2 );
    add_DFF_gate( gate_name_2, new_net_2, origin_CK, origin_Q );
}

void DGraph::fix_cycle_two_level( Gate* curgate )
{
    Wire* origin_D  = curgate -> get_wire_list(0);
    Wire* origin_CK = curgate -> get_wire_list(1);
    Wire* origin_Q  = curgate -> get_wire_list(2);
    string wire_name_1 = curgate -> get_name();
    string gate_name_1 = curgate -> get_name();
    wire_name_1.append("_cycle2_1_w");
    gate_name_1.append("_cycle2_1");

    Wire* new_net_1 = new Wire( wire_name_1, 0 );
    addition_wire.push_back( wire_name_1 );
    

    
    map_wire[ wire_name_1 ] = new_net_1;
    curgate -> set_wire_list( 2, new_net_1 );
    add_DFF_gate( gate_name_1, new_net_1, origin_CK, origin_Q );
}

void DGraph::Deadlock_elimination()
{

    Gate* curgate;
    Gate* tempgate;
    vector< Gate* > cycle_one_level;
    vector< Gate* > cycle_two_level;

    //cout << "ONE LEVEL CYCLE:\n";
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
        fix_cycle_one_level( curgate );
    }

    if( !cycle_one_level.empty() )
    {
        gate_wire_connection();
        DFS_DFF_connection();
    }



    //cout << "TWO LEVEL CYCLE:\n";
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
                        //cout << "push: " << pushgate -> get_name() << endl;
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
        fix_cycle_two_level( curgate );
    }
    
    if( !cycle_two_level.empty() )
    {
        gate_wire_connection();
        DFS_DFF_connection();
    }




}



void DGraph::build_node_connection( )
{

    Gate* curgate;
    int   id = 0;
    Node* curnode;
 
    for ( map<string ,Gate*>::iterator it= map_gate.begin(); it!= map_gate.end(); ++it)
    {
        curgate = it -> second;
        if( !isDFF( curgate ) )
            continue;
        
		curnode = new Node( curgate -> get_name(),id, curgate );
		add_node( curnode );
        curgate   -> set_node( curnode );
        ++id;
    } 

    for ( map<string ,Gate*>::iterator it= map_gate.begin(); it!= map_gate.end(); ++it)
    {
        curgate = it -> second;
        if( !isDFF( curgate ) )
            continue;
        curnode = curgate -> get_node();
        for( size_t i = 0; i < curgate -> fanin_dff_size(); i++ )
            curnode -> add_fanin( curgate -> get_fanin_dff(i) -> get_node() );   

        for( size_t i = 0; i < curgate -> fanout_dff_size(); i++ )
            curnode -> add_fanout( curgate -> get_fanout_dff(i) -> get_node() );    
    }
}

void DGraph::create_c_element_module( )
{
    stringstream ss;
    string module_name = "c_element";
    ss << "module c_element ( A, B, Y );\n";
    ss << "    input A, B;\n";
    ss << "    output Y;\n";
    ss << "    wire S, R, Y_bar;\n";
    ss << "    and AND1 ( S, A, B );\n";  
    ss << "    nor NOR1 ( R, A, B );\n"; 
    ss << "    nor SR_LATCH0 ( Y_bar, S, Y );\n";
    ss << "    nor SR_LATCH1 ( Y    , R, Y_bar );\n";
    ss << "endmodule\n";
    string m = ss.str();
    //cout << m;
    map_module[ module_name ] = new Module( module_name );
    map_module[ module_name ] -> set_content( m );
}


void DGraph::create_c_element_rst_module( )
{
    stringstream ss;
    string module_name = "c_element_rst";
    ss << "module c_element_rst ( A, B, rst, ini, Y );\n";
    ss << "    input A, B, rst, ini;\n";
    ss << "    output Y;\n";
    ss << "    wire S_temp, R_temp, S, R, Y_bar;\n";
    ss << "    and AND1 ( S_temp, A, B );\n";  
    ss << "    nor NOR1 ( R_temp, A, B );\n"; 
    ss << "    assign S = (rst)? S_temp: ini;\n"; 
    ss << "    assign R = (rst)? R_temp: ~ini;\n"; 
    ss << "    nor SR_LATCH0 ( Y_bar, S, Y );\n";
    ss << "    nor SR_LATCH1 ( Y    , R, Y_bar );\n";
    ss << "endmodule\n";
    string m = ss.str();
    //cout << m;
    map_module[ module_name ] = new Module( module_name );
    map_module[ module_name ] -> set_content( m );
}


void DGraph::create_NCL_register_module()
{
    stringstream ss;
    string module_name = "NCL_register";
    ss << "module NCL_register ( A_0, A_1, ack_in, Y_0, Y_1 );\n";
    ss << "    input A_0, A_1, ack_in;\n";
    ss << "    output Y_0, Y_1;\n";
    ss << "    c_element_rst C0( A_0, ack_in, rst, 1'b0, Y_0 );\n";  
    ss << "    c_element_rst C1( A_1, ack_in, rst, 1'b0, Y_1 );\n";
    ss << "endmodule\n";
    string m = ss.str();
    //cout << m;
    map_module[ module_name ] = new Module( module_name );
    map_module[ module_name ] -> set_content( m );
}

void DGraph::create_NCL_register_rst_module()
{
    stringstream ss;
    string module_name = "NCL_register_rst";
    ss << "module NCL_register_rst ( A_0, A_1, ack_in, rst, Y_0, Y_1 );\n";
    ss << "    input A_0, A_1, ack_in, rst;\n";
    ss << "    output Y_0, Y_1;\n";
    ss << "    c_element_rst C0( A_0, ack_in, rst, 1'b1, Y_0 );\n";  
    ss << "    c_element_rst C1( A_1, ack_in, rst, 1'b0, Y_1 );\n";
    ss << "endmodule\n";
    string m = ss.str();
    //cout << m;
    map_module[ module_name ] = new Module( module_name );
    map_module[ module_name ] -> set_content( m );
}


void DGraph::create_completion_module(string module_name, size_t parameter )
{
    stringstream ss;
    ss << "module " << module_name << "( Y";
    for( size_t i = 0; i < parameter; ++i )
    {
        ss << ", I_" << i << "_" << 0;
        ss << ", I_" << i << "_" << 1;
    }
    ss << ");\n";
    ss << "    output Y;\n";
    ss << "    input ";
    for( size_t i = 0; i < parameter; ++i )
    {
        if( i != 0 )
            ss << ",";
        ss << " I_" << i << "_" << 0;
        ss << ", I_" << i << "_" << 1;
    }
    ss << ";\n";
    ss << "    wire S, R, Q, Q_bar";
    for( size_t i = 0; i < parameter; ++i )
        ss << ", I_" << i;
    ss << ";\n";

    for( size_t i = 0; i < parameter; ++i )
        ss << "    or O" << i << " ( I_" << i << ", I_" << i << "_0, I_" << i << "_1 );\n";
    

    if( parameter == 1 )
    {
        ss << "    assign S = I_0;\n";
        ss << "    assign R = ~I_0;\n";

    }
    else
    {
        ss << "    and AND1 ( S";
        for( size_t i = 0; i < parameter; ++i )
            ss << ", I_" << i;
        ss << ");\n";
        ss << "    nor NOR1 ( R";
        for( size_t i = 0; i < parameter; ++i )
            ss << ", I_" << i;
        ss << ");\n";
    }
    ss << "    nor SRLATCH0 ( Q_bar, S, Q);\n";
    ss << "    nor SRLATCH1 ( Q, R, Q_bar);\n";
    ss << "    assign Y = Q_bar;\n";

    ss << "endmodule" << endl;

    string m = ss.str();
    //cout << m;
    map_module[ module_name ] = new Module( module_name );
    map_module[ module_name ] -> set_content( m );
    
}

bool comp (Wire* i, Wire* j) { return ( i -> id < j -> id ); }



void DGraph::create_completion_gate( string type, string name, Gate* curgate )
{  
    vector< Wire* > ack_in_vec;
    for( size_t i = 0; i < curgate -> fanout_dff_size(); i++ )
        ack_in_vec.push_back( curgate -> get_fanout_dff(i) -> get_wire_list( 2 ) );
    
    sort( ack_in_vec.begin(), ack_in_vec.end(), comp );

    //cout << curgate -> get_name() << " " << ack_in_vec.size() << endl;

    bool match = false;    
    for( size_t i = 0; i < ack_gate_list.size(); i++ )
    {
        if( ack_in_vec.size() + 1 != ack_gate_list[i] -> wire_list_size() )
            continue;

        match = true;
        for( size_t j = 0; j < ack_in_vec.size(); j++ )
        {
            if( ack_in_vec[j] -> id != ack_gate_list[i] -> get_wire_list( j + 1) -> id )
            {
                match = false;
                break;
            }

        }

        if( match )
        {
            curgate -> set_wire_list( 1, ack_gate_list[i] -> get_wire_list(0) );
            curgate -> set_port_list( 1, "ack_in" );
            break;
        }
    }

    if( !match )
    {
        Gate* newgate = new Gate( name, type );
        newgate -> add_port_list( "Y" );
        for( size_t i = 0; i < ack_in_vec.size(); ++i )
        {
            stringstream ss0; 
            ss0 << " I_" << i;
            newgate -> add_port_list( ss0.str() );
        }
        
        
        string wirename = curgate -> get_name();
        wirename.append("_ack");
        Wire* ack_wire = new Wire( wirename, 0);
        ack_wire_list.push_back( ack_wire );
        
        newgate -> add_wire_list( ack_wire );
        for( size_t i = 0; i < ack_in_vec.size(); ++i )
            newgate -> add_wire_list( ack_in_vec[i] );
        ack_gate_list.push_back( newgate );
        
        curgate -> set_wire_list( 1, ack_wire );
        curgate -> set_port_list( 1, "ack_in" );
    }
}

void DGraph::completion_detection()
{

    Gate* curgate;
    Node* curnode;
 
    for ( map<string ,Gate*>::iterator it= map_gate.begin(); it!= map_gate.end(); ++it)
    {
        curgate = it -> second;
        if( !isDFF( curgate ) )
            continue;


        string module_name = "completion";
        string index_s = to_string( curgate -> fanout_dff_size() );
        module_name.append( index_s );

        //cout << curgate -> get_name() << "  " << curgate -> fanout_dff_size() << endl; 

        if( curgate -> fanout_dff_size() == 0 )
            continue;

        map<string ,Module*>::iterator iter = map_module.find( module_name );
        if(iter == map_module.end())
            create_completion_module( module_name, curgate -> fanout_dff_size() );
        string gatename = curgate -> get_name();
        gatename.append("_com");
        //Wire* ack_wire = new Wire(wirename, 0);        
        //ack_wire_list.push_back( wirename );
        //map_wire[ wirename ] = ack_wire;
        create_completion_gate( module_name, gatename, curgate );   

    }

}


