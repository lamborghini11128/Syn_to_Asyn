#include <iostream>
#include <iomanip>
#include "DG.h"

using namespace std;
DGraph* Global_DG;

void file_parser();
void graph_generator();
void graph_analysis();

int main(int argc, char** argv)     
{
    if( argc == 0 )
        graph_generator();
    else if( argc == 1 )
    {
        file_parser();
    }
    
    return 0;
}

void file_parser()
{
}

void graph_generator()
{
}

void graph_analysis()
{
}
