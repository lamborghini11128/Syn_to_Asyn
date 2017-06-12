#include <vector>

using namespace std;

#ifndef CYCLE_LIST_H
#define CYCLE_LIST_H
class Cycle;
class Cycle_list
{
    public:
        Cycle_list() {}
        ~Cycle_list() {}
        int get_size() {return cycle_list.size();}
        Cycle* get_cycle(int i) {return cycle_list[i];}
        void add_cycle(Cycle* c) {cycle_list.push_back(c);}
        
    private:
        vector <Cycle*> cycle_list;


};

#endif
