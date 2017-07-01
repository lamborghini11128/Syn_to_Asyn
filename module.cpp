#include <sstream>
#include "module.h"
using namespace std;

bool Wire::is_equal(const string& check) {
    if (check==name) {return true;}
    else if (check.find('[')!=string::npos) {
        int start = check.find('[');
        int end = check.find(']', start);
        string idx = check.substr(start+1, end-start-1);
        string cmp = check.substr(0, start);
        //while (cmp[cmp.length()-1]==' ') {cmp.pop_back();}
        cmp = cmp + " " + idx;
        return cmp == name;
    }
    else { return false; }
}

Module::~Module() {
    //for (int i=0; i!=wires.size(); ++i) { delete wires[i]; }
}

void Module::setModuleType() {
    stringstream ssName(module_code[0]);
    string buf;
    ssName >> buf;  // buf == "module"
    ssName >> module_type;
}

void Module::setInOutWires() {
    string buf;
    cout << module_type << " setting in/out wires" << endl;
    for (int i=1; i<module_code.size(); ++i) {
        stringstream ssLine(module_code[i]);
        ssLine >> buf;
        if (buf=="input") {
            while (ssLine>>buf) {
                if (buf[0]=='[') {
                    int n1 = buf.find(':');
                    int max = stoi(buf.substr(1, n1-1));
                    int n2 = buf.find(']');
                    int min = stoi(buf.substr(n1+1, n2-n1-1));
                    ssLine >> buf;
                    //buf.pop_back();
                    for (int i=min; i<=max; ++i) {
                        string new_wire_name = buf+" "+to_string(i);
                        Wire* new_wire = new Wire(new_wire_name);
                        input_ports.push_back(new_wire);
                        wires.push_back(new_wire);
                    }
                }
                else {
                    if (buf[buf.length()-1]==',') {buf.pop_back();}
                    Wire* new_wire = new Wire(buf);
                    input_ports.push_back(new_wire);
                    wires.push_back(new_wire);
                }
            }
        }
        else if (buf=="output") {
            while (ssLine>>buf) {
                if (buf[0]=='[') {
                    int n1 = buf.find(':');
                    int max = stoi(buf.substr(1, n1-1));
                    int n2 = buf.find(']');
                    int min = stoi(buf.substr(n1+1, n2-n1-1));
                    ssLine >> buf;
                    //buf.pop_back();
                    for (int i=min; i<=max; ++i) {
                        string new_wire_name = buf+" "+to_string(i); 
                        Wire* new_wire = new Wire(new_wire_name);
                        output_ports.push_back(new_wire);
                        wires.push_back(new_wire);
                    }
                }
                else {
                    if (buf[buf.length()-1]==',') {buf.pop_back();}
                    Wire* new_wire = new Wire(buf);
                    output_ports.push_back(new_wire);
                    wires.push_back(new_wire);
                }
            }
        }
        else if (buf=="wire") {
            while (ssLine>>buf) {
                if (buf[0]=='[') {
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
                    if (buf[buf.length()-1]==',') {buf.pop_back();}
                    Wire* new_wire = new Wire(buf);
                    wires.push_back(new_wire);
                }
            }
        }
        else if (buf=="assign") {}
        else { break; }
    }
}

void Module::build_graph(vector<Node*>& PI_list, vector<Node*>& PO_list, const vector<Module*> module_lib, DGraph* DG) {
    cout << module_type << " " << module_name << "building graph..." << endl;
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
        int i=1;
        string type, name;
        for (; i!=module_code.size(); ++i) {
            stringstream ssLine(module_code[i]);
            ssLine >> type;
            if (type!="input" && type!="output" && type!="wire" && type!="assign") { break; }
        }

        vector<Module*> tmp_module_list;
        for (int j=i; j!=module_code.size()-1; ++j) {
            stringstream ssLine(module_code[j]);
            ssLine >> type >> name;
            Module* module_instance = new Module(type, name);
            tmp_module_list.push_back(module_instance);

            if (type=="DFFQX1") { DFF_parse_and_link(module_code[j], module_instance); }
            else if (type=="EDFFX1") {EDFF_parse_and_link(module_code[i], module_instance);}
            else if (type=="DFFRX1") {DFFRX1_parse_and_link(module_code[i], module_instance);}
            else {
                for (int k=0; k!=module_lib.size(); ++k) {
                    if (type==module_lib[k]->module_type) {
                        module_instance->get_input_ports() = module_lib[k]->get_input_ports();
                        module_instance->get_output_ports() = module_lib[k]->get_output_ports();
                        module_instance->get_wires() = module_lib[k]->get_wires();
                        module_parse_and_link(module_code[j], module_instance);
                        break;
                    }
                }
                gate_parse_and_link(module_code[j], module_instance);
            }
        }

        vector<Node*> breakdown_node_list;
        vector<Module*> breakdown_module_list;
        vector<Node*> constructed_node_list;
        for (int i=0; i!=input_ports.size(); ++i) {
            dfs_circuit_to_graph(input_ports[i], PI_list, PO_list, breakdown_node_list, breakdown_module_list,
             constructed_node_list);
        }

        for (int i=0; i!=breakdown_module_list.size(); ++i) {
            Node* broken_node = breakdown_node_list[i];
            breakdown_module_list[i]->build_graph(broken_node->get_fanin_list(), broken_node->get_fanout_list(), module_lib, DG);
        }

        for (auto& node: constructed_node_list) {DG->add_node(*node);}
        for (auto& mod: tmp_module_list) {delete mod;}
    }
}

void dispose_parentheses(string& type, string& name, const string& code) {
    if (code.find('(')==string::npos) {return;}
    int start = code.find('(');
    int end = code.find(')', start);
    type = code.substr(1, start-1);
    name = code.substr(start+1, end-start-1);
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
//   EDFFX1 \out_reg[4]  ( .D(N1827), .E(n1861), .CK(clk), .Q(out[4]) );
void Module::EDFF_parse_and_link(const string& line_code, Module* module_instance) {
    stringstream ss(line_code);
    string buffer;
    ss >> buffer >> buffer >> buffer >> buffer;
    string wire_type;
    string in1_name;
    dispose_parentheses(wire_type, in1_name, buffer);
    ss >> buffer;
    string in2_name;
    dispose_parentheses(wire_type, in2_name, buffer);
    ss >> buffer >> buffer;
    string out_name;
    dispose_parentheses(wire_type, out_name, buffer);
    //cout << in_name << out_name;
    for (auto& w: wires) {
        if (w->is_equal(in1_name)) {
            w->add_fanout(module_instance);
            module_instance->add_fanin(w);
        }
        else if (w->is_equal(in2_name)) {
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
//DFFRX1 \round10_key_reg[127]  ( .D(n2591), .CK(clock), .RN(resetn), .QN(n3031) );
void Module::DFFRX1_parse_and_link(const string& line_code, Module* module_instance) {
    stringstream ss(line_code);
    string buffer;
    ss >> buffer >> buffer >> buffer >> buffer;
    string wire_type;
    string in_name;
    dispose_parentheses(wire_type, in_name, buffer);
    ss >> buffer >> buffer;
    string out1_name;
    dispose_parentheses(wire_type, out1_name, buffer);
    ss >> buffer;
    string out2_name;
    dispose_parentheses(wire_type, out2_name, buffer);
    //cout << in_name << out_name;
    for (auto& w: wires) {
        if (w->is_equal(in_name)) {
            w->add_fanout(module_instance);
            module_instance->add_fanin(w);
        }
        else if (w->is_equal(out1_name)) {
            w->add_fanin(module_instance);
            module_instance->add_fanout(w);
        }
        else if (w->is_equal(out2_name)) {
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
        if (buffer==")") {break;}
        string wire_type, wire_name;
        dispose_parentheses(wire_type, wire_name, buffer);
        if (wire_name=="1'b0") {continue;}
        vector<string> instance_wire_array, wire_array;
        module_instance->get_wire_array(wire_type, instance_wire_array);
        get_wire_array(wire_name, wire_array);

        for(auto& wire: instance_wire_array) {
            for (int i=0; i!=module_instance->get_input_ports().size(); ++i) {
            //for (auto& in_wire: module_instance->get_input_ports()) {
                if (module_instance->get_input_ports()[i]->is_equal(wire)) {
                //if (in_wire->is_equal(wire)) {
                    for (auto& w: wires) {
                        for (auto& wi: wire_array) {
                            if (w->is_equal(wi)) {
                                w->add_fanout(module_instance);
                                module_instance->add_fanin(w);
                                break;
                            }
                        }
                    }
                }
            }
            for (auto& out_wire: module_instance->get_output_ports()) {
                if (out_wire->is_equal(wire)) {
                    for (auto& w: wires) {
                        for (auto& wo: wire_array) {
                            if (w->is_equal(wire)) {
                                w->add_fanin(module_instance);
                                module_instance->add_fanout(w);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    return;
}
void Module::gate_parse_and_link(const string& line_code, Module* module_instance) {
    module_instance->set_combinational();
    stringstream ss(line_code);
    string buffer;
    ss >> buffer >> buffer >> buffer;
    while (ss>>buffer) {
        if (buffer==");") {break;}
        while (buffer.find(')')==string::npos) {
            string subbuf;
            ss >> subbuf;
            buffer += subbuf;
        }
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

void classify_add_node(Module* module, vector<Node*>& dff_node_list, vector<Node*> gate_node_list) {
    Node* parent_node;
        if (module->module_type=="DFFQX1" || module->module_type=="DFFRX1" || module->module_type=="EDFFX1") {
            parent_node = new Node(module->module_name, dff_node_list.size());
            dff_node_list.push_back(parent_node);
        }
        else {
            parent_node = new Node(module->module_name, -2);
            gate_node_list.push_back(parent_node);
        }
}
void Module::dfs_circuit_to_graph_prime(vector<Node*>& dff_node_list) {
    vector<Module*> traverse_record;
    vector<Node*> gate_node_list;
    for (auto& pi_wire: input_ports) {
        for (auto& root_mod: pi_wire->get_fanout()) {
            if (root_mod->module_id==-1) {
                classify_add_node(root_mod, dff_node_list, gate_node_list);
                traverse_record.push_back(root_mod);
                while (traverse_record.size()) {
                    Module* parent_module = traverse_record[traverse_record.size()-1];
                    for (auto& o_wire: parent_module->output_ports) {
                        for (auto& child_module: o_wire->get_fanout()) {
                        }
                    }
                    Node* child_node;
                    traverse_record.pop_back();
                }
            }
        }
    }
}

void Module::dfs_circuit_to_graph(Wire* start_wire, vector<Node*>& start_node_list, vector<Node*>& end_node_list,
     vector<Node*>& breakdown_node_list, vector<Module*>& breakdown_module_list, vector<Node*>& constructed_node_list, int depth) {
    cout << "depth: " << depth << endl;
    start_wire->mark=1;
    for (auto& out_wire: output_ports) {
        if (start_wire==out_wire) {
            for (auto& i_node: start_node_list) {
                for (auto& o_node: end_node_list) {
                    i_node->add_fanout(o_node);
                    o_node->add_fanin(i_node);
                }
            }
            return;
        }
    }
    for (auto& module: start_wire->get_fanout()) {
        if (module->module_type=="DFFQX1" || module->module_type=="EDFFX1" || module->module_type=="DFFRX1") {
            if (module->module_id!=-1) {
                for (auto& start_node: start_node_list) {
                    start_node->add_fanout(constructed_node_list[module->module_id]); 
                    constructed_node_list[module->module_id]->add_fanin(start_node);
                }
                return;
            }
            else {
                Node* dff_node = new Node(module->module_name, constructed_node_list.size());
                cout << "contructing node..." << module->module_name << endl;
                module->module_id=constructed_node_list.size();
                constructed_node_list.push_back(dff_node);
                for (auto& start_node: start_node_list) {
                    start_node->add_fanout(dff_node);
                    dff_node->add_fanin(start_node);
                }
                vector<Node*> nl = {dff_node};
                for (auto& out_wire: module->get_output_ports()) {
                    if (!out_wire->mark) {dfs_circuit_to_graph(out_wire, nl, end_node_list,
                        breakdown_node_list, breakdown_module_list, constructed_node_list, depth+1);}
                }
            }
        }
        else {
            /*
            bool is_breakdown_module=false;
            for (auto& m: module_include_set) {
                bool inserted = false;
                if (m->module_type==module->module_type) {
                    is_breakdown_module = true;
                    for (auto& n: constructed_node_list) {
                        if (n->name==module->module_name) {
                            for (auto& start_node:start_node_list) { start_node->add_fanout(n); }
                            inserted = true;
                            break;
                        }
                    }
                    if (!inserted) {
                        Node* module_node = new Node(module->module_name, constructed_node_list.size());
                        constructed_node_list.push_back(module_node);
                        breakdown_node_list.push_back(module_node);
                        breakdown_module_list.push_back(module);
                        for (auto& start_node: start_node_list) { start_node->add_fanout(module_node); }
                        vector<Node*> nl = {module_node};
                        for (auto& out_wire: module->get_output_ports()) { this->dfs_circuit_to_graph(out_wire, nl, 
                            end_node_list, breakdown_node_list, breakdown_module_list, constructed_node_list); }
                    }
                }
            }
            */
            for (auto& out_wire: module->get_output_ports()) { if (!out_wire->mark) {dfs_circuit_to_graph(out_wire, start_node_list,
                end_node_list, breakdown_node_list, breakdown_module_list, constructed_node_list, depth+1);} }
                /*
            if (!is_breakdown_module) {
                for (auto& out_wire: module->get_output_ports()) { this->dfs_circuit_to_graph(out_wire, start_node_list,
                 end_node_list, breakdown_node_list, breakdown_module_list, constructed_node_list); }
            }
            */
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
        if (buf=="DFFQX1" || buf=="EDFFX1" || buf=="DFFRX1") {
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
            if (buf_type==module_lib[j]->module_type) {
                if (module_include_set.find(module_lib[j]) == module_include_set.end()) {
                    module_include_set.insert(module_lib[j]);
                    module_lib[j]->is_included=true;
                }
            }
        }
    }
}

void Module::get_wire_array(string wire_type, vector<string>& wire_array) {
    if (wire_type.find(':')!=string::npos) {
        int sp  = wire_type.find(':');
        int srt = wire_type.find('[');
        int end = wire_type.find(']');
        int beg_idx = stoi(wire_type.substr(srt, sp-srt));
        int end_idx = stoi(wire_type.substr(sp, end-sp));
        for (int i=beg_idx; i!=end_idx; ++i) {
            wire_array.push_back(wire_type.substr(0, srt)+" "+to_string(i));
        }
        return;
    }
    for (auto& w: wires) {
        if (w->name.find(' ')!=string::npos) {
            int sp = w->name.find(' ');
            string pure_name = w->name.substr(0, sp);
            if (wire_type == pure_name) {
                wire_array.push_back(w->name);
            }
        }
        else if (w->is_equal(wire_type)) {
            wire_array.push_back(w->name);
            return;
        }
    }
}