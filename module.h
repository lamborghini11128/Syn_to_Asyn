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
	Wire(string& name): name(name) {}
	void add_fanin(Module* gate) { fanin.push_back(gate); }
	void add_fanout(Module* gate) { fanout.push_back(gate); }
	bool is_equal(const string& check) { return check == name;}
	vector<Module*> get_fanin() { return fanin;}
private:
	string name;
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
	}
	Module(const string& type, const string& name): module_type(type), module_name(name) {}
	~Module();

	void module_including(const vector<Module*>&);
	const vector<string>& get_module_code() { return module_code; }
	void build_graph(vector<Node*>&, vector<Node*>&, const vector<Module*>);
	string module_type;
	string module_name;
	bool is_included;
private:
	void setModuleType();
	void setInOutWires();
	void combinationalCheck();	// check if the module is combinational
	void DFF_parse_and_link(const string&);
	void module_parse_and_link(const string& line_code);
	void gate_parse_and_link(const string& line_code);
	void dfs_circuit_to_graph(const Wire* start_wire, vector<Node*>&, vector<Node*>&,
	     const vector<Module*>& module_lib, vector<Node*>& breakdown_node_list, vector<Module*>& breakdown_module_list);

	
	vector<string> module_code;	// each element in vector contain one line of code of the module
	set<Module*> module_include_set;
	bool is_combinational;
	vector<Wire*> input_ports;
	vector<Wire*> output_ports;
	vector<Wire*> wires;
	//DGraph module_graph;
};

#endif