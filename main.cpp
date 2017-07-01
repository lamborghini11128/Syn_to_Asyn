#include <iostream>
#include <iomanip>
#include <fstream>
#include "DG.h"
#include "module.h"

using namespace std;
DGraph* Global_DG;

void file_parser(const char*);
void graph_generator();
void graph_analysis();
void dfs();

int main(int argc, char** argv)     
{
    if( argc == 1 )
        graph_generator();
    else if( argc == 2 )
    {
        file_parser(argv[1]);
    }
    
    return 0;
}

void file_parser(const char* gate_file)
{
    fstream fgate_file(gate_file);
    if (!fgate_file.is_open()) {cout <<"open failed..."<<endl; return;}
    vector<Module*> module_lib;

    vector<Module*> top_module_list;
    vector<string> module_code;
    string line;
    bool is_reading=false;
    // read in the module code and construct module_lib
    while (getline(fgate_file, line)) {
        /*if (line[0]=='m') {
            fgate_file.seekg(0);
            break;
        }*/
        if (fgate_file.peek() == 'm') {break;}
    }
    while (getline(fgate_file, line)) {
        //while (line[0]=='\n') {line = line.substr(1);}
        //while (line.find('\n')!=string::npos) {line[line.find('\n')]=' ';}
        while (line[line.length()-1]!=';') {
            if (line=="endmodule") {break;}
            string tail;
            if (getline(fgate_file, tail)) {line+=tail;}
            else {break;}
        }
        if (line[line.length()-1]==';') {line.pop_back();}
        if      (line.substr(0, 6)!="module" && !is_reading)    continue;   // garbage message
        else if (line.substr(0, 6)=="module" && !is_reading) {
            module_code.push_back(line);
            is_reading = true;
        }
        else if (line!="endmodule" && is_reading) {
            if (line!="") {module_code.push_back(line);}
        }
        else if (line=="endmodule" && is_reading) {
            module_code.push_back(line);
            Module* one_module = new Module(module_code);
            module_lib.push_back(one_module);
            module_code.clear();
            is_reading = false;
        }
        else 
            try { throw(line); }
        catch(string exception) { cout << exception << endl; }
    }

    // determine the top module
    for (int i=0; i<module_lib.size(); ++i) { module_lib[i]->module_including(module_lib); }
    for (int i=0; i<module_lib.size(); ++i) {
        if (!module_lib[i]->is_included) { top_module_list.push_back(module_lib[i]); }
    }
    
    // build DG
    Global_DG = new DGraph();
    Node PI_node("PI", -4), PO_node("PO", -3);
    vector<Node*> PI; PI.push_back(&PI_node);
    vector<Node*> PO; PO.push_back(&PO_node);
    for (int i=0; i<top_module_list.size(); ++i) {
        top_module_list[i]->build_graph(PI, PO, module_lib, Global_DG);
    }
    Global_DG->add_node(PI_node);
    Global_DG->add_node(PO_node);

    //Global_DG->find_cycle();
    //Global_DG->find_fvs();

    for (int i=0; i<module_lib.size(); ++i) {
        for (auto& wire: module_lib[i]->get_wires()) {delete wire;}
        delete module_lib[i];
    }

    Global_DG->print_list();
}

void graph_generator()
{
}

void graph_analysis()
{
}
