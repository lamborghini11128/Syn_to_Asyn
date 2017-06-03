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
    vector<Module*> module_lib;

    vector<Module*> top_module_list;
    vector<string> module_code;
    string line;
    bool is_reading=false;
    // read in the module code and construct module_lib
    while (getline(fgate_file, line)) {
        if      (line.substr(0, 6)!="module" && !is_reading)    continue;   // garbage message
        else if (line.substr(0, 6)=="module" && !is_reading) {
            module_code.push_back(line);
            is_reading = true;
        }
        else if (line!="endmodule" && is_reading)   module_code.push_back(line);
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
    //cout << top_module_list.size() <<endl;
    
    // build DG
    Global_DG = new DGraph();
    Node PI_node, PO_node;
    vector<Node*> PI; PI.push_back(&PI_node);
    vector<Node*> PO; PO.push_back(&PO_node);
    for (int i=0; i<top_module_list.size(); ++i) {
        top_module_list[i]->build_graph(PI, PO, module_lib);
    }

    for (int i=0; i<module_lib.size(); ++i)    { delete module_lib[i]; }
}

void graph_generator()
{
}

void graph_analysis()
{
}