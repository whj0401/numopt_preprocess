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
    
        bool can_add_stmt() const
        { return !is_return; }
        
        Path();
    };
    
    class Paths;
    
    class Loop;
    
    class Path_Loop_Paths
    {
    public:
        Path path;
        Loop *loop;
        Paths *follow_paths;
        
        Path_Loop_Paths(const Path &_path, Loop *_loop = nullptr, Paths *_paths = nullptr) :
                path(_path), loop(_loop), follow_paths(_paths)
        {}
        
        bool has_follow_paths() const
        { return (follow_paths != nullptr); }
        
        void add_stmt(const SgStatement *stmt);
        
        void add_str(const string &str);
        
        void enter_new_block();
        
        void leave_cur_block();
    };
    
    class Paths
    {
        void add_path(const Path &p);
    
        void add_path_loop_paths(const Path_Loop_Paths &p);
    
    public:
        size_t ID;
        vector<Path_Loop_Paths> list;
        
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
