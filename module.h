#include <string>
#include <vector>
#include <set>
#include <iostream>
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
private:
	string name;
	vector<Module*> fanin;
	vector<Module*> fanout;
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
	~Module();
	void module_including(const vector<Module*>&);
	const vector<string>& get_module_code() { return module_code; }
	string module_type;
	string module_name;
	bool is_included;
private:
	void setModuleType();
	void setInOutWires();
	void combinationalCheck();	// check if the module is combinational
	vector<string> module_code;	// each element in vector contain one line of code of the module
	set<Module*> module_include_set;
	bool is_combinational;
	vector<Wire*> input_ports;
	vector<Wire*> output_ports;
	vector<Wire*> wires;
};

/*
class Gate
{
public:
	Gate(string& name): name(name) {}
	void add_fanin(Wire* wire) { fanin.push_back(wire);}
	void add_fanout(Wire* wire) { fanout.push_back(wire); }
private:
	string name;
	vector<Wire*> fanin;
	vector<Wire*> fanout;
};
*/
#endif