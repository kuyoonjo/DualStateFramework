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
#include <memory>

#include "Export.h"
#include "Declaration.h"
#include "Task.h"
#include "Runnable.h"
#include "Debug.h"

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
        std::shared_ptr<std::vector<std::shared_ptr<Task>>> tasks;
    private:
    };
}
#endif
