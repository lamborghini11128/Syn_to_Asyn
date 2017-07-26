#include <string>
#include <vector>
#include <set>
#include <iostream>
#include "DG.h"
using namespace std;

#ifndef MODULE_H
#define MODULE_H

class Gate;
class Wire
{
public:
	Wire(string& name, int t): name(name), wire_type(t){}
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
private:
    vector<Gate*> fanin_gate;
    vector<Gate*> fanout_gate;
	string name;
    int    wire_type; // 0: wire; 1: input; 2:output;
};

class Gate
{
public:
	Gate(string& name, string& type ): name(name), type(type) { flag = -1; level = -1; }
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
    void   set_wire_list( int i, Wire* w ) { wire_list[i] = w; }
    
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

    int  get_flag()         { return flag; }
    void set_flag( int i )  { flag = i; }
    int  get_level()        { return level; }
    void set_level( int i ) { level = i; }

private:
    vector< Wire*  > fanin_wire;
    vector< Wire*  > fanout_wire;
    vector< string > port_list;
    vector< Wire*  > wire_list;
    vector< Gate* >  fanin_dff;
    vector< Gate* >  fanout_dff;

    string      name;
    string      type;
    int         flag;
    int         level;
};  

#endif
