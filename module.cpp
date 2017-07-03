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
        vector<Module*> module_list;
        for (int j=i; j!=module_code.size()-1; ++j) {
            stringstream ssLine(module_code[j]);
            ssLine >> type >> name;
            Module* module_instance = new Module(type, name);
            module_list.push_back(module_instance);
            Module* module_for_special_dff;

            if (type=="DFFQX1") { DFF_parse_and_link(module_code[j], module_instance); }
            else if (type=="EDFFX1") {
                module_for_special_dff = new Module("AND", "pre_"+name);
                module_list.push_back(module_for_special_dff);
                EDFF_parse_and_link(module_code[i], module_instance, module_for_special_dff);
            }
            else if (type=="DFFRX1") {DFFRX1_parse_and_link(module_code[i], module_instance, module_for_special_dff);}
            else {gate_parse_and_link(module_code[j], module_instance);}
        }
        cout << "circuit established" << endl;

        vector<Node*> constructed_node_list;
        dfs(constructed_node_list, PI_list[0], PO_list[0]);
        remove_gate_node(constructed_node_list);
        /* this part is recurrsive version
        for (int i=0; i!=input_ports.size(); ++i) {
            if (input_ports[i]->get_fanout().size()) {
                dfs_circuit_to_graph(input_ports[i], PI_list, PO_list, breakdown_node_list, breakdown_module_list, constructed_node_list);
            }

        }
        */
        for (auto& module: module_list) {delete module;}
        for (auto& node: constructed_node_list) {
            if(node->get_node_id()) DG->add_node(*node);
            else {delete node;}
        }
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
void Module::EDFF_parse_and_link(const string& line_code, Module* module_instance, Module* gate) {
    stringstream ss(line_code);
    string buffer;
    ss >> buffer >> buffer;
    buffer = "wire_pre_"+buffer;
    Wire* small_wire = new Wire(buffer);
    gate->add_fanout(small_wire);
    small_wire->add_fanin(gate);
    small_wire->add_fanout(module_instance);

    ss >> buffer >> buffer;
    string wire_type;
    string in1_name;
    dispose_parentheses(wire_type, in1_name, buffer);
    ss >> buffer;
    string in2_name;
    dispose_parentheses(wire_type, in2_name, buffer);
    ss >> buffer >> buffer;
    string out_name;
    dispose_parentheses(wire_type, out_name, buffer);
    for (auto& w: wires) {
        if (w->is_equal(in1_name)) {
            w->add_fanout(gate);
            gate->add_fanin(w);
        }
        else if (w->is_equal(in2_name)) {
            w->add_fanout(gate);
            gate->add_fanin(w);
        }
        else if (w->is_equal(out_name)) {
            w->add_fanin(module_instance);
            module_instance->add_fanout(w);
        }
    }   
    return;
}
//DFFRX1 \round10_key_reg[127]  ( .D(n2591), .CK(clock), .RN(resetn), .QN(n3031) );
void Module::DFFRX1_parse_and_link(const string& line_code, Module* module_instance, Module* gate) {
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

/* this function is for hierarchy structure
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
}*/
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

void link(Node* i, Node* o) {
    i->add_fanout(o);
    o->add_fanin(i);
}
void Module::dfs(vector<Node*>& node_list, Node* i_node, Node* o_node) {
    vector<Module*> dfs_stack;
    for (auto& iw: input_ports) {
        for (auto& ow: output_ports) {
            if (ow==iw) {link(i_node, o_node); break;}
        }
        for (auto& m: iw->get_fanout()) {
            if (m->module_id==-1) {
                dfs_stack.push_back(m);
                int is_dff=0;
                if (m->module_type=="DFFQX1" || m->module_type=="EDFFX1" || m->module_type=="DFFRX1") {is_dff=1;}
                Node* new_node = new Node(m->module_name, is_dff);
                m->module_id = node_list.size();
                node_list.push_back(new_node);
                link(i_node, new_node);
            }
        }
    }
    while (dfs_stack.size()) {
        Module* parent = dfs_stack[dfs_stack.size()-1];
        dfs_stack.pop_back();
        for (auto& iw: parent->output_ports) {
            for (auto& ow: output_ports) {
                if (ow==iw) {link(node_list[parent->module_id], o_node); break;}
            }
            for (auto& m: iw->get_fanout()) {
                if (m->module_id==-1) {
                    dfs_stack.push_back(m);
                    int is_dff=0;
                    if (m->module_type=="DFFQX1" || m->module_type=="EDFFX1" || m->module_type=="DFFRX1") {is_dff=1;}
                    Node* new_node = new Node(m->module_name, is_dff);
                    m->module_id = node_list.size();
                    node_list.push_back(new_node);
                    link(node_list[parent->module_id], new_node);
                }
                else {link(node_list[parent->module_id], node_list[m->module_id]);}
            }
        }
    }
}

void Module::remove_gate_node(vector<Node*>& node_list) {
    for (auto& n: node_list) {
        if (!n->get_node_id()) {
            for (int i=0; i!=n->get_fanin_list().size(); ++i) {
                for (int j=0; j<n->get_fanin_list()[i]->get_fanout_list().size(); ++j) {
                    if (n->get_fanin_list()[i]->get_fanout_list()[j]==n)
                        n->get_fanin_list()[i]->get_fanout_list().erase(n->get_fanin_list()[i]->get_fanout_list().begin()+j);
                }
            }
            for (int i=0; i!=n->get_fanout_list().size(); ++i) {
                for (int j=0; j<n->get_fanout_list()[i]->get_fanin_list().size(); ++j) {
                    if (n->get_fanout_list()[i]->get_fanin_list()[j]==n)
                        n->get_fanout_list()[i]->get_fanin_list().erase(n->get_fanout_list()[i]->get_fanin_list().begin()+j);
                }
            }
            for (auto& in: n->get_fanin_list()) {
                for (auto& on: n->get_fanout_list()) {link(in, on);}
            }
        }
    }
}

// this is recurrsive version
void Module::dfs_circuit_to_graph(Wire* start_wire, vector<Node*>& start_node_list, vector<Node*>& end_node_list,
     vector<Node*>& breakdown_node_list, vector<Module*>& breakdown_module_list, vector<Node*>& constructed_node_list, int depth) {
    cout << "depth: " << depth << endl;
    //start_wire->mark=1;
    if (start_node_list.size()) {start_wire->mark = start_node_list[0]->get_node_id();}
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
                //return;
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
                for (auto& out_wire: module->get_output_ports()) { //if (out_wire->mark!=)
                    dfs_circuit_to_graph(out_wire, nl, end_node_list,
                    breakdown_node_list, breakdown_module_list, constructed_node_list, depth+1);
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
            for (auto& out_wire: module->get_output_ports()) {
                //if (out_wire->mark!=start_node_list[0]->get_node_id())
                    dfs_circuit_to_graph(out_wire, start_node_list,
                end_node_list, breakdown_node_list, breakdown_module_list, constructed_node_list, depth+1);
            }
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