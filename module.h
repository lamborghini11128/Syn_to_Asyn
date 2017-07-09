#include <string>
#include <vector>
#include <set>
#include <iostream>
#include "DG.h"
using namespace std;

#ifndef MODULE_H
#define MODULE_H

class Module;

class Wire
{
public:
	Wire(string& name): name(name), mark(-1) {}
	void add_fanin(Module* gate) { fanin.push_back(gate); }
	void add_fanout(Module* gate) { fanout.push_back(gate); }
	bool is_equal(const string& check);
	vector<Module*>& get_fanin() { return fanin;}
    vector<Module*>& get_fanout() { return fanout;}
	string name;
    int mark;
private:
    vector<Module*> fanin;
    vector<Module*> fanout;
    vector<Wire*> link;
};

class Module
{
public:
	Module(const vector<string>& code): module_code(code) {
		setModuleType();
		setInOutWires();
		combinationalCheck();
		is_included=false;
        module_id=-1;
	}
	Module(const string& type, const string& name): module_type(type), module_name(name) {module_id=-1;}

	void module_including(const vector<Module*>&);
	const vector<string>& get_module_code() { return module_code; }
	void build_graph(vector<Node*>&, vector<Node*>&, const vector<Module*>, DGraph*);
    void add_fanin(Wire* wire) { input_ports.push_back(wire); }
    void add_fanout(Wire* wire) { output_ports.push_back(wire); }
    vector<Wire*>& get_input_ports() {return input_ports;}
    vector<Wire*>& get_output_ports() {return output_ports;}
    vector<Wire*>& get_wires() {return wires;}
	string module_type;
	string module_name;
    bool is_included;
    int module_id;
    void set_combinational() {is_combinational=true;}
    void combinationalCheck();  // check if the module is combinational
    void get_wire_array(string, vector<string>&);
private:
    void setModuleType();
    void setInOutWires();
    void DFF_parse_and_link(const string&, Module*);
    void EDFF_parse_and_link(const string&, Module*, Module*);
    void DFFRX1_parse_and_link(const string&, Module*, Module*);
    //void module_parse_and_link(const string&, Module*);
    void gate_parse_and_link(const string&, Module*);
    void dfs_circuit_to_graph(Wire*, vector<Node*>&, vector<Node*>&, vector<Node*>&, vector<Module*>&, vector<Node*>&, int depth=0);
    void dfs_circuit_to_graph_prime(vector<Node*>&, vector<Node*>&, vector<Node*>&);
    void dfs(vector<Node*>&, Node*, Node*);
    void remove_gate_node(vector<Node*> &);
    
    vector<string> module_code; // each element in vector contain one line of code of the module
    set<Module*> module_include_set;
    bool is_combinational;
    vector<Wire*> input_ports;
    vector<Wire*> output_ports;
    vector<Wire*> wires;
};

#endif