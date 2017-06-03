#include <sstream>
#include "module.h"
using namespace std;

bool Wire::is_equal(const string& check) {
     if (check==name) { return true; }
     else if (check.find('[')) {
        int start = check.find('[');
        int end = check.find(']');
        string idx = check.substr(start, end-start);
        string cmp = check.substr(0, start+1) + " " + idx;
        return cmp == idx;
     }
     else { return false; }
}

Module::~Module() {
    //for (int i=0; i!=input_ports.size(); ++i) { delete input_ports[i]; }
    //for (int i=0; i!=output_ports.size(); ++i) { delete output_ports[i]; }
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
                    string new_wire_name = buf+" "+to_string(i); 
                    Wire* new_wire = new Wire(new_wire_name);
                    input_ports.push_back(new_wire);
                    wires.push_back(new_wire);
                }
            }
            else {
                Wire* new_wire = new Wire(buf);
                input_ports.push_back(new_wire);
                wires.push_back(new_wire);
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
                    string new_wire_name = buf+" "+to_string(i); 
                    Wire* new_wire = new Wire(new_wire_name);
                    output_ports.push_back(new_wire);
                    wires.push_back(new_wire);
                }
            }
            else {
                Wire* new_wire = new Wire(buf);
                output_ports.push_back(new_wire);
                wires.push_back(new_wire);
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
                    string new_wire_name = buf+" "+to_string(i); 
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

void Module::build_graph(vector<Node*>& PI_list, vector<Node*>& PO_list, const vector<Module*> module_lib) {
    if (is_combinational) {
        for (auto& pi: PI_list) {
            for (auto& po: PO_list) {
                pi->add_fanout(po);
                po->add_fanin(pi);
            }
        }
        return;
    }

    else {
        int i=0;
        string type, name;
        for (; i!=module_code.size(); ++i) {
            stringstream ssLine(module_code[i]);
            ssLine >> type;
            if (type!="input" && type!="output" && type!="wire" && type!="assign") { break; }
        }

        for (int j=i; j<module_code.size(); ++j) {
            stringstream ssLine(module_code[i]);
            ssLine >> type >> name;
            Module module_instance(type, name);

            if (type=="DFFQX1") { this->DFF_parse_and_link(module_code[i], &module_instance); }
            else {
                for (int k=0; k!=module_lib.size(); ++k) {
                    if (type==module_lib[k]->module_type) {
                        module_instance.get_input_ports() = module_lib[k]->get_input_ports();
                        module_instance.get_output_ports() = module_lib[k]->get_output_ports();
                        this->module_parse_and_link(module_code[i], &module_instance);
                        break;
                    }
                }
                module_instance.gate_parse_and_link(module_code[i], &module_instance);
            }
        }

        vector<Node*> breakdown_node_list;
        vector<Module*> breakdown_module_list;
        for (int i=0; i!=input_ports.size(); ++i) {
            this->dfs_circuit_to_graph(input_ports[i], PI_list, PO_list, breakdown_node_list, breakdown_module_list);
        }

        for (int i=0; i!=breakdown_module_list.size(); ++i) {
            Node* broken_node = breakdown_node_list[i];
            breakdown_module_list[i]->build_graph(broken_node->get_fanin_list(), broken_node->get_fanout_list(), module_lib);
        }
    }
}

void dispose_parentheses(string& type, string& name, const string& code) {
    int start = code.find('(');
    int end = code.find(start, ')');
    type = code.substr(1, start-1);
    name = code.substr(start, end-start);
}

void Module::DFF_parse_and_link(const string& line_code, Module* module_instance) {
    stringstream ss(line_code);
    string buffer;
    ss >> buffer >> buffer >> buffer >> buffer;
    string wire_type;
    string in_name;
    dispose_parentheses(wire_type, in_name, buffer);
    ss >> buffer >> buffer;
    string out_name;
    dispose_parentheses(wire_type, out_name, buffer);
    cout << in_name << out_name;
    for (auto& w: wires) {
        if (w->is_equal(in_name)) {
            w->add_fanout(module_instance);
            module_instance->add_fanin(w);
        }
        else if (w->is_equal(out_name)) {
            w->add_fanin(module_instance);
            module_instance->add_fanout(w);
        }
    }   
    return;
}
void Module::module_parse_and_link(const string& line_code, Module* module_instance) {
    stringstream ss(line_code);
    string buffer;
    ss >> buffer >> buffer >> buffer;
    while(ss>>buffer) {
        if (buffer==");") {break;}
        string wire_type, wire_name;
        dispose_parentheses(wire_type, wire_name, buffer);
        for (auto& in_wire: module_instance->get_input_ports()) {
            if (in_wire->is_equal(wire_type)) {
                for (auto& w: wires) {
                    if (w->is_equal(wire_name)) {
                        w->add_fanout(module_instance);
                        module_instance->add_fanin(w);
                        break;
                    }
                }
            }
        }
        for (auto& out_wire: module_instance->get_output_ports()) {
            if (out_wire->is_equal(wire_type)) {
                for (auto& w: wires) {
                    if (w->is_equal(wire_name)) {
                        w->add_fanin(module_instance);
                        module_instance->add_fanout(w);
                        break;
                    }
                }
            }
        }
    }
    return;
}

void Module::gate_parse_and_link(const string& line_code, Module* module_instance) {
    stringstream ss(line_code);
    string buffer;
    ss >> buffer >> buffer >> buffer >> buffer;
    while (ss>>buffer) {
        if (buffer==");") {break;}
        string wire_type, wire_name;
        dispose_parentheses(wire_type, wire_name, buffer);
        if (wire_type=="CO" || wire_type=="S" || wire_type=="Y") {
            for (auto& w: wires) {
                if (w->is_equal(wire_name)) {
                    w->add_fanin(module_instance);
                    module_instance->add_fanout(w);
                    break;
                }
            }
        }
        else {
            for (auto& w: wires) {
                if (w->is_equal(wire_name)) {
                    w->add_fanout(module_instance);
                    module_instance->add_fanin(w);
                    break;
                }
            }
        }
    }
    return;
}
void Module::dfs_circuit_to_graph(Wire* start_wire, vector<Node*>& start_node_list, vector<Node*>& end_node_list,
     vector<Node*>& breakdown_node_list, vector<Module*>& breakdown_module_list) {
    for (auto& module: start_wire->get_fanout()) {
        if (module->module_type=="DFFQX1") {
            for (auto& start_node: start_node_list) {}
        }
    }
    return;
}

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

void Module::module_including(const vector<Module*>& module_lib) {
    string buf_type;
    for (int i=0; i<module_code.size(); ++i) {
        stringstream ssLine(module_code[i]);
        ssLine >> buf_type;
        for (int j=0; j<module_lib.size(); ++j) {
            if (buf_type==module_lib[j]->module_name) {
                if (module_include_set.find(module_lib[j]) == module_include_set.end()) {
                    module_include_set.insert(module_lib[j]);
                    is_included=true;
                }
            }
        }
    }
}