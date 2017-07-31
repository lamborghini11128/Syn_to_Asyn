#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <vector>
//#include <string>
#include <set>

#include <sstream>
#include <algorithm>
#include <map>
#include <queue>
#include <string.h>


#include "Cycle.h"
#include "Cycle_list.h"
#ifndef DG_H
#define DG_H
using namespace std;

static int WireId = 0;

class Gate;
class Wire
{
public:
	Wire(string& name, int t): name(name), wire_type(t){ addition = false; ack = false; id = ++WireId; }
    ~Wire(){}
    void add_fanin_gate ( Gate* g ) { fanin_gate.push_back( g ); }
    void add_fanout_gate( Gate* g ) { fanout_gate.push_back( g ); }
    Gate* get_fanin_gate ( int i )  { return fanin_gate[i]; }
    Gate* get_fanout_gate( int i )  { return fanout_gate[i]; }
    size_t fanin_gate_size()        { return fanin_gate.size();  }
    size_t fanout_gate_size()       { return fanout_gate.size(); }
    void fanin_gate_clear()         { fanin_gate.clear();  }
    void fanout_gate_clear()        { fanout_gate.clear(); }


    int    get_wire_type()          { return wire_type; }
    string get_name()               { return name;}
    string set_name();
    string get_name_v();     
    string get_name(int);        
    bool addition;
    bool ack;
    int  id;
private:
    vector<Gate*> fanin_gate;
    vector<Gate*> fanout_gate;
	string name;
    int    wire_type; // 0: wire; 1: input; 2:output;
};

class Node;
class Gate
{
public:
	Gate(string& name, string& type ): name(name), type(type) { flag = -1; level = -1; fvs = false; }
    ~Gate(){}
    void add_fanin_wire ( Wire* w ) { fanin_wire.push_back( w ); }
    void add_fanout_wire( Wire* w ) { fanout_wire.push_back( w ); }
    Wire* get_fanin_wire ( int i )  { return fanin_wire[i]; }
    Wire* get_fanout_wire( int i )  { return fanout_wire[i]; }
    size_t fanin_wire_size()        { return fanin_wire.size(); }
    size_t fanout_wire_size()       { return fanout_wire.size(); }
    void fanin_wire_clear()         { fanin_wire.clear(); }
    void fanout_wire_clear()        { fanout_wire.clear(); }
    
    void add_port_list( string p )  { port_list.push_back( p ); }
    void add_wire_list( Wire*  w )  { wire_list.push_back( w ); }
    string get_port_list( int i )   { return port_list[ i ]; }
    Wire* get_wire_list( int i )    { return wire_list[ i ]; }
    size_t port_list_size()         { return port_list.size(); }
    size_t wire_list_size()         { return wire_list.size(); }
    void   set_wire_list( int i, Wire* w  ) { wire_list[i] = w; }
    void   set_port_list( int i, string p ) { port_list[i] = p; }

    void add_fanin_dff ( Gate* g ) { fanin_dff.push_back( g ); }
    void add_fanout_dff( Gate* g ) { fanout_dff.push_back( g ); }
    Gate* get_fanin_dff ( int i )  { return fanin_dff[i]; }
    Gate* get_fanout_dff( int i )  { return fanout_dff[i]; }
    size_t fanin_dff_size()        { return fanin_dff.size(); }
    size_t fanout_dff_size()       { return fanout_dff.size(); }
    void   fanin_dff_clear()       { fanin_dff.clear(); }
    void   fanout_dff_clear()      { fanout_dff.clear(); }


    void gate_add_fanin( int i );
    void gate_add_fanout( int i );

    string get_name() { return name; }
    string get_type() { return type; }
    void   set_type( string t) { type = t; }

    int  get_flag()         { return flag; }
    void set_flag( int i )  { flag = i; }
    int  get_level()        { return level; }
    void set_level( int i ) { level = i; }
    Node* get_node()        { return node; }
    void  set_node( Node* n ) { node = n; }

    void set_fvs() { fvs = true; }
    bool get_fvs() { return fvs; }
private:
    vector< Wire*  > fanin_wire;
    vector< Wire*  > fanout_wire;
    vector< string > port_list;
    vector< Wire*  > wire_list;
    vector< Gate* >  fanin_dff;
    vector< Gate* >  fanout_dff;

    
    Node*       node;
    string      name;
    string      type;
    int         flag;
    int         level;
    bool        fvs;
};  


class Node
{
    public:
        Node();
        Node(string name, int id): name(name), id(id) {}
        Node(string name, int id, Gate* g): name(name), id(id), DFF(g) {}
       
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

	    int id;
        
        //Detect cycle part
        Node* get_fanin(int i) {return fanin_list[i];}
        Node* get_fanout(int i) {return fanout_list[i];}
        int get_fanin_size() {return fanin_list.size();}
        int get_fanout_size() {return fanout_list.size();}
        Cycle* get_cycle(int i) {return cycle_list[i];}
        void add_cycle(Cycle* c) {cycle_list.push_back(c);}
        int get_cycle_size() {return cycle_list.size();}
        void set_node_DFS_id (int i) {DFS_id=i;}
        int get_node_DFS_id () {return DFS_id;}
        void set_node_id (int i) {id=i;}
        int get_node_id () {return id;}
        void set_in_stack_or_not (bool s) {in_stack_or_not=s;}
        bool get_in_stack_or_not () {return in_stack_or_not;}
        //void set_in_cycle_or_not (bool c) {in_cycle_or_not=c;}
        //bool get_in_cycle_or_not () {return in_cycle_or_not;}
        void set_traversed_or_not (bool t) {traversed_or_not=t;}
        bool get_traversed_or_not () {return traversed_or_not;}
        Gate* get_DFF()         { return DFF; }
        void  set_DFF( Gate* g ){ DFF = g;} 
        int   get_level() { return level;}
        void  set_level(int i ) { level = i; }

        
    private:
        vector< Node*>  fanout_list;
        vector< Node*>  fanin_list;
    
        //Detect cycle part
        vector <Cycle*> cycle_list;         //cycles that contain the node
        int DFS_id;                             //DFS id in stack
        bool in_stack_or_not;               //flag indicate that the node is currently in stack or not
        //bool in_cycle_or_not;               //flag indicate that the node is currently in cycle or not
        bool traversed_or_not;              //flag indicate that the node is traversed or not
        Gate* DFF;
        int level;
        
};

class Module
{
    public:
        Module(){}
        Module( string& type ): type(type) { }
        ~Module(){}


        string get_type() { return type; }
        void   set_content( string s ) { content = s; }
        string get_content() { return content; }

        vector< Wire* > input_list;           
        vector< Wire* > output_list;   
        vector< Wire* > wire_list;        
        vector< Gate* > gate_list;           

    private:

        string type;
        string content;

};


// directed graph
class DGraph
{
    public:
        DGraph();
        ~DGraph();
        //Graph generation part
        void add_node( Node* newNode) { node_list.push_back(newNode); }
        const void print_list() {
            for(int i=0; i!=node_list.size(); ++i) {
                cout << i+1 << ": " << node_list[i] -> name << endl;
                cout << "  fanin:  ";
                for (int j=0; j!=node_list[i] -> get_fanin_size(); ++j) 
                    printf("%s ", node_list[i] -> get_fanin(j)->name.c_str());
                
                cout <<endl<< "  fanout: ";
                for (int j=0; j!=node_list[i] -> get_fanout_size(); ++j) 
                    printf("%s ", node_list[i] -> get_fanout(j)-> name.c_str());
                cout << endl<<endl;
            }
        }
        
        //Detect cycle part
        void find_cycle();
        void find_fvs();
	    void print_status();
        Cycle_list* get_cycle_list() {return cycle_list;}         
        void add_node_to_fvs(Node* n) {fvs.push_back(n);}
        int get_fvs_size() {return fvs.size();}
        Node* get_fvs_node (int i) {return fvs[i];}
	    Node* get_node (int i) {return node_list[i];}

        // levelization 
        void levelization();


        //Parse file and build gates 
        void build_wire( string , int& ); //
        void build_gate( string ); //
        void new_wire( string , int );//
        void gate_add_fanin( Gate* g, Wire* w );//
        void gate_add_fanout( Gate* g, Wire* w );//
        void input_output_DFF();//
        void print_gate();//
        void print_module();//
        void print_Verilog();//
        void print_module_declaration();
        void print_input_declaration();
        void print_output_declaration();
        void print_wire_declaration();

        void DFF_modification();//
        void gate_wire_connection();//

        void add_AND_gate( string, Wire*, Wire*, Wire* );
        void add_OR_gate ( string, Wire*, Wire*, Wire* );
        void add_DFF_gate( string, Wire*, Wire*, Wire* );
        void add_INV_gate( string, Wire*, Wire* );
        void DFS_DFF_connection();
        void DFF_connection( Gate*, vector< Gate* >& );
        void DFF_levelization();
        void Deadlock_elimination();
        void build_node_connection();
        void fix_cycle_one_level( Gate* curgate );
        void fix_cycle_two_level( Gate* curgate );

        void completion_detection();
        void create_completion_module(string, size_t );
        void create_c_element_module ();
        void create_NCL_register_module ();
        void create_c_element_rst_module ();
        void create_NCL_register_rst_module ();
        void create_completion_gate( string, string, Gate* );

        void set_module_dec( string s ) { module_declaration = s; }
        void set_input_dec ( string s ) { input_declaration.push_back(s); }
        void set_output_dec( string s ) { output_declaration.push_back(s); }
        void set_wire_dec  ( string s ) { wire_declaration.push_back(s); }
        
    private:
        vector< Node* > node_list;           


        //Detect cycle part
        Cycle_list* cycle_list;       
        vector<Node*> fvs;


        //vector< string > line_list;
        map< string, Wire* > map_wire;
        map< string, Gate* > map_gate;
        string CLKNAME; 
        map< string, Module* > map_module;
        string module_declaration;
        vector< string > input_declaration;
        vector< string > output_declaration;
        vector< string > wire_declaration;
        vector< string > addition_wire;
        vector< Wire* > ack_wire_list;
        vector< Gate* >  ack_gate_list;
};


#endif
