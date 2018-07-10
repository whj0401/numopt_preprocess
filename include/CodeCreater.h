//
// Created by whj on 7/9/18.
//

#ifndef CODE_ANALYSE_CODECREATER_H
#define CODE_ANALYSE_CODECREATER_H

#include <vector>
#include <iostream>
#include "Path.h"
#include "Loop.h"

namespace le
{
    class CodeCreater
    {
    private:
        vector<Paths *> paths_list;
        vector<Loop *> loop_list;
    public:
        CodeCreater();
    
        Paths *create_paths();
    
        Paths *copy_paths(const Paths *_p);
    
        Paths *copy_paths_with_no_return_path(const Paths *_p);
    
        Loop *create_loop();
    
        Loop *copy_loop(const Loop *_l);
    
        ~CodeCreater();
    };
    
    extern CodeCreater paths_pool;
}

#endif //CODE_ANALYSE_CODECREATER_H
