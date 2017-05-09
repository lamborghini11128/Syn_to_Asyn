#include <string>
#include <vector>
#include <sstream>
using namespace std;

typedef string wire;

class Module
{
public:
	Module(const vector<string>& code): module_code(code) {
		setModuleName();
		setInOutputs();
		combinationalCheck();
		is_included=false;
	}
	void module_including(const vector<Module*>&);
	void setIncluded() { is_included=true; }
	string module_name;
	bool is_included;
private:
	void setModuleName();
	void setInOutputs();
	void combinationalCheck();	// check if the module is combinational
	vector<string> module_code;	// each element in vector contain one line of code of the module
	vector<Module*> module_include_list;
	bool is_combinational;
	vector<wire> input_ports;
	vector<wire> output_ports;
};

void Module::setModuleName() {
	stringstream ssName(module_code[0]);
	string buf;
	ssName >> buf;	// buf == "module"
	ssName >> module_name;
}

void Module::setInOutputs() {
	string buf;
	for (int i=0; i<module_code.size(); ++i) {
		stringstream ssLine(module_code[i]);
		ssLine >> buf;
		if (buf=="input") {
			if (ssLine>>buf && buf[0]=='[') {
				ssLine >> buf;
				input_ports.push_back(buf);
			}
			else	input_ports.push_back(buf);
		}
		else if (buf=="output") {
			if (ssLine>>buf && buf[0]=='[') {
				ssLine >> buf;
				output_ports.push_back(buf);
			}
			else	output_ports.push_back(buf);
		}
	}
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

void Module::module_including(const vector<Module*>& module_list) {
	string buf_word;
	for (int i=0; i<module_code.size(); ++i) {
		stringstream ssLine(module_code[i]);
		ssLine >> buf_word;
		for (int j=0; j<module_list.size(); ++j) {
			if (buf_word==module_list[j]->module_name) {
				bool have_included=false;
				for (int k=0; k<module_include_list.size(); ++k) {
					if (module_list[j]==module_include_list[k]) { have_included=true; }
				}
				if (!have_included) {
					module_include_list.push_back(module_list[j]);
					module_list[j]->setIncluded();
				}
			}
		}
	}
}