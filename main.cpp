#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "DG.h"
#include "module.h"

using namespace std;
DGraph* Global_DG;

void file_parser(const char*);
void graph_generator();
void graph_analysis();

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
	vector<Module> module_list;
	vector<string> module_code;
	string line, word;
	bool is_reading=false;
	while (getline(fgate_file, line)) {
		if 		(line.substr(0, 6)!="module" && !is_reading)	continue;	// garbage message
		else if (line.substr(0, 6)=="module" && !is_reading) {
			module_code.push_back(line);
			is_reading = true;
		}
		else if (line!="endmodule" && is_reading)	module_code.push_back(line);
		else if (line=="endmodule" && is_reading) {
			module_code.push_back(line);
			Module one_module(module_code);
			module_list.push_back(one_module);
			module_code.clear();
			is_reading = false;
		}
		else 
			try	{ throw(line); }
		catch(string exception)	{ cout << exception << endl; }
	}
}

void graph_generator()
{
}

void graph_analysis()
{
}
