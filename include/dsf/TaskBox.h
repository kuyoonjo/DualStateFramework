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

#include "Export.h"
#include "Declaration.h"
#include "Task.h"
namespace dsf
{
    class DSF_API TaskBox
    {
    public:
        bool isEmpty();
        void push(Task* task);
        Task* pop();
    private:
        std::vector<Task*>* tasks;
        
    };
}
#endif
