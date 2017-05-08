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
	}
	~Module();
private:
	void setModuleName();
	void setInOutputs();
	void combinationalCheck();	// check if the module is combinational
	vector<string> module_code;	// each element in vector contain one line of code of the module
	string module_name;
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