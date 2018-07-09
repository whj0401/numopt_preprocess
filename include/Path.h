//
// Created by whj on 7/9/18.
//

#ifndef CODE_ANALYSE_PATH_H
#define CODE_ANALYSE_PATH_H

#include <vector>
#include <string>
#include <sstream>
#include "rose.h"

namespace le
{
    using namespace std;
    
    class Path
    {
    public:
        bool is_return;
        SgExpression *ret_expr;
        int block_layer;
        vector<string> s;
        
        void add_stmt(const SgStatement *stmt);
        
        void add_str(const string &str);
        
        void enter_new_block();
        
        void leave_cur_block();
        
        void write_to_ss(stringstream &ss) const;
        
        Path();
    };
    
    class Paths
    {
        void add_path(const Path &p);
    
    public:
        vector<Path> list;
        
        void add_stmt(const SgStatement *stmt);
        
        void add_str(const string &str);
        
        void enter_new_block();
        
        void leave_cur_block();
        
        Paths copy_no_end();
        
        void merge(const Paths &p);
        
        void set_return();
        
        string to_string() const;
        
        Paths();
    };
}

#endif //CODE_ANALYSE_PATH_H
