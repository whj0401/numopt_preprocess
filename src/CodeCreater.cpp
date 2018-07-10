//
// Created by whj on 7/9/18.
//

#include "CodeCreater.h"

namespace le
{
    CodeCreater::CodeCreater()
    {
    
    }
    
    Paths *CodeCreater::create_paths()
    {
        Paths *ret = new Paths();
        ret->ID = paths_list.size();
        paths_list.push_back(ret);
        return ret;
    }
    
    Paths *CodeCreater::copy_paths(const le::Paths *_p)
    {
        Paths *ret = create_paths();
        ret->list = _p->list;
        for (auto &p : ret->list)
        {
            // copy loop
            p.loop = copy_loop(p.loop);
            // recursively copy follow paths
            p.follow_paths = copy_paths(p.follow_paths);
        }
        return ret;
    }
    
    Paths *CodeCreater::copy_paths_with_no_return_path(const le::Paths *_p)
    {
        // this may return a paths object with no path inside
        Paths *ret = create_paths();
        ret->list.clear();
        for (auto &p : _p->list)
        {
            if (p.path.can_add_stmt())
            {
                if (p.has_follow_paths())
                {
                    Paths *tmp_follow_paths = copy_paths_with_no_return_path(p.follow_paths);
                    if (tmp_follow_paths->list.empty()) continue;
                    ret->list.push_back(p);
                    ret->list.back().loop = copy_loop(p.loop);
                    ret->list.back().follow_paths = tmp_follow_paths;
                }
                else
                {
                    ret->list.push_back(p);
                }
            }
        }
        return ret;
    }
    
    Loop *CodeCreater::create_loop()
    {
        Loop *ret = new Loop();
        ret->ID = loop_list.size();
        loop_list.push_back(ret);
        return ret;
    }
    
    Loop *CodeCreater::copy_loop(const le::Loop *_l)
    {
        if (_l == nullptr) return nullptr;
        Loop *ret = create_loop();
        ret->lval_vars = _l->lval_vars;
        ret->out_loop_vars = _l->out_loop_vars;
        return ret;
    }
    
    CodeCreater::~CodeCreater()
    {
        for (auto &ptr : paths_list)
        {
            delete ptr;
            ptr = nullptr;
        }
        for (auto &ptr : loop_list)
        {
            delete ptr;
            ptr = nullptr;
        }
    }
    
    CodeCreater paths_pool;
}