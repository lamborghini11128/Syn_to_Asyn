#include <sstream>
#include "module.h"
using namespace std;


string Wire::get_name_v()
{
    size_t find = name.find("[");
    string name_v;
    if( find == string::npos )
    {
        name_v = name;
        if( wire_type == 1 )
            name_v.append("_i");
        if( wire_type == 2 )
            name_v.append("_o");
    }
    else
    {
        name_v = name.substr(0, find );
        if( wire_type == 1 )
            name_v.append("_i");
        if( wire_type == 2 )
            name_v.append("_o");
        name_v.append( name.substr(find));
    }

    return name_v;

}

string Wire::set_name()
{
    size_t find = name.find("[");
    string name_v;
    if( find == string::npos )
    {
        name_v = name;
        if( wire_type == 1 )
            name_v.append("_i");
        if( wire_type == 2 )
            name_v.append("_o");
    }
    else
    {
        name_v = name.substr(0, find );
        if( wire_type == 1 )
            name_v.append("_i");
        if( wire_type == 2 )
            name_v.append("_o");
        name_v.append( name.substr(find));
    }
    name = name_v;
    return name;
}


void Gate::gate_add_fanin( int i )
{
    Wire* w = wire_list[i];
    this -> add_fanin_wire ( w );
    w    -> add_fanout_gate( this );
}

void Gate::gate_add_fanout( int i )
{
    Wire* w = wire_list[i];
    this -> add_fanout_wire( w );
    w    -> add_fanin_gate ( this );
}
