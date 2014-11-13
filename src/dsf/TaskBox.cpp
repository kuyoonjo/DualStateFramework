//
//  TaskBox.cpp
//  dsf
//
//  Created by Yu Chen on 10/17/14.
//
//

#include <dsf/TaskBox.h>

namespace dsf {
    TaskBox::TaskBox()
    {
        this->tasks = std::shared_ptr<std::vector<std::shared_ptr<Task>>>(new std::vector<std::shared_ptr<Task>>());
        Debug("A TaskBox Object has been created.");
    }
    
    TaskBox::~TaskBox()
    {
        Debug("A TaskBox Object has been removed.");
    }
    
    bool TaskBox::isEmpty()
    {
        return this->tasks->empty();
    }
    
    void TaskBox::push(dsf::Task *task)
    {
        this->tasks->push_back(std::shared_ptr<Task>(task));
    }
    
    Task* TaskBox::pop()
    {
        Task* task = this->tasks->back().get();
        this->tasks->pop_back();
        return task;
    }
    
    void TaskBox::process()
    {
        while (!this->isEmpty())
        {
            Debug("start a Task ...");
            Task* task = this->pop();
            (*task->taskFunction)(task->taskArguments.get());
            Debug("finish a Task.");
        }
    }
}
