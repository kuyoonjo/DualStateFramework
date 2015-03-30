//
//  TaskBox.cpp
//  dsf
//
//  Created by Yu Chen on 10/17/14.
//
//

#include <dsf/TaskBox.h>

namespace dsf
{
    TaskBox::TaskBox()
    {
        this->tasks = new std::vector<Task*>();
    }
    
    TaskBox::~TaskBox()
    {
        for (std::vector<Task*>::iterator i = this->tasks->begin(); i != this->tasks->end(); ++i)
        {
            delete *i;
        }
        delete this->tasks;
    }
    
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
    
    void TaskBox::process()
    {
        while (!this->isEmpty())
        {
            Task* task = this->pop();
            (*task->taskFunction)(task->to, task->from, task->taskArgument);
            delete task;
        }
    }
}
