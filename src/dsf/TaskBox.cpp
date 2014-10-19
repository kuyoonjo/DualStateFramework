//
//  TaskBox.cpp
//  dsf
//
//  Created by Yu Chen on 10/17/14.
//
//

#include <dsf/TaskBox.h>

namespace dsf {
    
    bool TaskBox::isEmpty()
    {
        return this->tasks->empty();
    }
    
    void TaskBox::push(dsf::Task *task)
    {
        this->tasks->push_back(task);
    }
    
    Task* TaskBox::pop()
    {
        Task* task = this->tasks->back();
        this->tasks->pop_back();
        return task;
    }
}
