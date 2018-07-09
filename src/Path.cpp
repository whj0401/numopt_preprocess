//
// Created by whj on 7/9/18.
//

#include "Path.h"
#include "common.h"

namespace le
{
    using namespace std;
    
    const string enter_block = "{";
    const string leave_block = "}";
    
    void Path::add_stmt(const SgStatement *stmt)
    {
        s.push_back(stmt->unparseToString());
    }
    
    void Path::add_str(const string &str)
    {
        s.push_back(str);
    }
    
    void Path::enter_new_block()
    {
        block_layer++;
        s.push_back(enter_block);
    }
    
    void Path::leave_cur_block()
    {
        block_layer--;
        assert(block_layer >= 0);
        s.push_back(leave_block);
    }
    
    void Path::write_to_ss(stringstream &ss) const
    {
        int block_layer = 0;
        string tab = generate_tab(block_layer);
        for (const auto &stmt : s)
        {
            if (stmt == enter_block)
            {
                ss << tab << stmt << endl;
                ++block_layer;
                tab = generate_tab(block_layer);
            }
            else if (stmt == leave_block)
            {
                --block_layer;
                tab = generate_tab(block_layer);
                ss << tab << stmt << endl;
            }
            else
            {
                ss << tab << stmt << endl;
            }
        }
    }
    
    Path::Path() : is_return(false), ret_expr(nullptr), block_layer(0)
    {}
    
    void Paths::add_path(const le::Path &p)
    {
        list.push_back(p);
    }
    
    void Paths::add_stmt(const SgStatement *stmt)
    {
        for (auto &p : list)
        {
            if (p.is_return) continue;
            p.add_stmt(stmt);
        }
    }
    
    void Paths::add_str(const string &str)
    {
        for (auto &p : list)
        {
            if (p.is_return) continue;
            p.add_str(str);
        }
    }
    
    Paths Paths::copy_no_end()
    {
        Paths copy;
        copy.list.clear();
        for (const auto &p : list)
        {
            if (p.is_return) continue;
            copy.add_path(p);
        }
        return copy;
    }
    
    void Paths::merge(const le::Paths &p)
    {
        for (const auto &tmp : p.list)
        {
            add_path(tmp);
        }
    }
    
    void Paths::set_return()
    {
        for (auto &p : list)
        {
            p.is_return = true;
        }
    }
    
    void Paths::enter_new_block()
    {
        for (auto &p : list)
        {
//            if(p.is_return) continue;
            p.enter_new_block();
        }
    }
    
    void Paths::leave_cur_block()
    {
        for (auto &p : list)
        {
            p.leave_cur_block();
        }
    }
    
    string Paths::to_string() const
    {
        stringstream ss;
        for (const auto &p : list)
        {
            p.write_to_ss(ss);
            ss << endl;
        }
        return ss.str();
    }
    
    Paths::Paths()
    {
        add_path(Path());
    }
}