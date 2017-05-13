#include <sstream>
#include "module.h"
using namespace std;

Module::~Module() {
    for (int i=0; i!=input_ports.size(); ++i) { delete input_ports[i]; }
    for (int i=0; i!=output_ports.size(); ++i) { delete output_ports[i]; }
    for (int i=0; i!=wires.size(); ++i) { delete wires[i]; }
}

void Module::setModuleType() {
    stringstream ssName(module_code[0]);
    string buf;
    ssName >> buf;  // buf == "module"
    ssName >> module_type;
}

void Module::setInOutWires() {
    string buf;
    for (int i=1; i<module_code.size(); ++i) {
        stringstream ssLine(module_code[i]);
        ssLine >> buf;
        if (buf=="input") {
            if (ssLine>>buf && buf[0]=='[') {
                int n1 = buf.find(':');
                int max = stoi(buf.substr(1, n1-1));
                int n2 = buf.find(']');
                int min = stoi(buf.substr(n1+1, n2-n1-1));
                ssLine >> buf;
                for (int i=min; i<=max; ++i) {
                    string new_wire_name = buf+"["+to_string(i)+"]"; 
                    Wire* new_wire = new Wire(new_wire_name);
                    input_ports.push_back(new_wire);
                }
            }
            else {
                Wire* new_wire = new Wire(buf);
                input_ports.push_back(new_wire);
            }
        }
        else if (buf=="output") {
            if (ssLine>>buf && buf[0]=='[') {
                int n1 = buf.find(':');
                int max = stoi(buf.substr(1, n1-1));
                int n2 = buf.find(']');
                int min = stoi(buf.substr(n1+1, n2-n1-1));
                ssLine >> buf;
                for (int i=min; i<=max; ++i) {
                    string new_wire_name = buf+"["+to_string(i)+"]"; 
                    Wire* new_wire = new Wire(new_wire_name);
                    output_ports.push_back(new_wire);
                }
            }
            else {
                Wire* new_wire = new Wire(buf);
                output_ports.push_back(new_wire);
            }
        }
        else if (buf=="wire") {
            if (ssLine>>buf && buf[0]=='[') {
                int n1 = buf.find(':');
                int max = stoi(buf.substr(1, n1-1));
                int n2 = buf.find(']');
                int min = stoi(buf.substr(n1+1, n2-n1-1));
                ssLine >> buf;
                for (int i=min; i<=max; ++i) {
                    string new_wire_name = buf+"["+to_string(i)+"]"; 
                    Wire* new_wire = new Wire(new_wire_name);
                    wires.push_back(new_wire);
                }
            }
            else {
                Wire* new_wire = new Wire(buf);
                wires.push_back(new_wire);
            }
        }
        else if (buf=="assign") {}
        else { break; }
    }
}

/*
void parse_inoutputs(const string&);
void Moduel::buildGraph() {
    if (is_combinational) { return; }
    int i=0;
    string buf;
    // jump to where module description starts
    for (; i<module_code.size(); ++i) {
        stringstream ssLine(module_code[i]);
        ssLine>>buf;
        if (buf!="input" && buf!="output" && buf!="wire" && buf!="assign") { break; }
    }
    // parse variables passed into mudule
    for (int j = i; j<module_code.size(); ++j) {
        stringstream ssLine(module_code[j]);
        string type, name;
        ssLine >> type >> name;
        ssLine >> buf;
        vector<string> iopass;
        while (ssLine >> buf && buf != ");") { iopass.push_back(buf); }
    }
}
*/

void Module::combinationalCheck() {
    string buf;
    is_combinational=true;
    for (int i=0; i<module_code.size(); ++i) {
        stringstream ssLine(module_code[i]);
        ssLine >> buf;
        if (buf=="DFFQX1") {
            is_combinational=false;
            return;
        }
    }
}

void Module::module_including(const vector<Module*>& module_list) {
    string buf_word;
    for (int i=0; i<module_code.size(); ++i) {
        stringstream ssLine(module_code[i]);
        ssLine >> buf_word;
        for (int j=0; j<module_list.size(); ++j) {
            if (buf_word==module_list[j]->module_name) {
                if (module_include_set.find(module_list[j]) == module_include_set.end()) {
                    module_include_set.insert(module_list[j]);
                    is_included=true;
                }
            }
        }
    }
}

//string parse_inoutputs(const string& in_output) {} 
