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
	Wire(string& name): name(name), is_visited(false) {}
	void add_fanin(Module* gate) { fanin.push_back(gate); }
	void add_fanout(Module* gate) { fanout.push_back(gate); }
	bool is_equal(const string& check);
	vector<Module*>& get_fanin() { return fanin;}
    vector<Module*>& get_fanout() { return fanout;}
	string name;
    bool is_visited;
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
        is_visited=false;
	}
	Module(const string& type, const string& name): module_type(type), module_name(name), is_visited(false) {}
	~Module();

	void module_including(const vector<Module*>&);
	const vector<string>& get_module_code() { return module_code; }
	void build_graph(vector<Node*>&, vector<Node*>&, const vector<Module*>);
    void add_fanin(Wire* wire) { input_ports.push_back(wire); }
    void add_fanout(Wire* wire) { output_ports.push_back(wire); }
    vector<Wire*>& get_input_ports() {return input_ports;}
    vector<Wire*>& get_output_ports() {return output_ports;}
	string module_type;
	string module_name;
    bool is_included;
    bool is_visited;
private:
    void setModuleType();
    void setInOutWires();
    void combinationalCheck();  // check if the module is combinational
    void DFF_parse_and_link(const string&, Module*);
    void module_parse_and_link(const string&, Module*);
    void gate_parse_and_link(const string&, Module*);
    void dfs_circuit_to_graph(Wire*, vector<Node*>&, vector<Node*>&, vector<Node*>&, vector<Module*>&);
    
    vector<string> module_code; // each element in vector contain one line of code of the module
    set<Module*> module_include_set;
    bool is_combinational;
    vector<Wire*> input_ports;
    vector<Wire*> output_ports;
    vector<Wire*> wires;
	//DGraph module_graph;
};

#endif