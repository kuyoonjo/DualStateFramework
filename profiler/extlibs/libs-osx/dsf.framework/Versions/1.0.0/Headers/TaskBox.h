//
//  Parallelable.h
//  DSF
//
//  Created by Yu Chen on 10/14/14.
//
//

#ifndef dsf_TaskBox_h
#define dsf_TaskBox_h

#include <vector>
#include <string>

#include "Export.h"
#include "Declaration.h"
#include "Task.h"
#include "Runnable.h"

namespace dsf
{
    class DSF_API TaskBox
    {
    public:
        TaskBox();
        virtual ~TaskBox();
        bool isEmpty();
        void push(Task* task);
        Task* pop();
        void process();
    protected:
        std::vector<Task*>* tasks;
    };
}
#endif
