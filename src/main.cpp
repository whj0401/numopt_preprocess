#include <iostream>
#include "rose.h"
#include "Program.h"

int main(int argc, char **argv)
{
    le::init_operator_str_map();
    le::run_project(argc, argv);
    return 0;
}