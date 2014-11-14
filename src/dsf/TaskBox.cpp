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
        this->tasks = new std::vector<Task*>();
        this->next = nullptr;
        Debug("A TaskBox Object has been created.");
    }
    
    TaskBox::~TaskBox()
    {
        for (std::vector<Task*>::iterator i = this->tasks->begin(); i != this->tasks->end(); ++i) {
            delete *i;
        }
        delete this->tasks;
        if (this->next) {
            delete this->next;
        }
        Debug("A TaskBox Object has been removed.");
    }
    
    bool TaskBox::isEmpty()
    {
        return this->tasks->empty();
    }
    
    void TaskBox::push(dsf::Task *task)
    {
        if (this->next)
        {
            this->next->tasks->push_back(task);
        }
        else
        {
            this->next = new TaskBox();
            this->push(task);
        }
    }
    
    Task* TaskBox::pop()
    {
        Task* task = this->tasks->back();
        this->tasks->pop_back();
        return task;
    }
    
    int TaskBox::receive()
    {
        if (!this->next || this->next->isEmpty())
        {
            return 0;
        }
        
        int count = 0;
        while (!this->next->isEmpty())
        {
            this->tasks->push_back(this->next->pop());
            count ++;
        }
        return count;
    }
    
    void TaskBox::process()
    {
        while (!this->isEmpty())
        {
            Debug("start a Task ...");
            Task* task = this->pop();
            (*task->taskFunction)(task->from, task->taskArguments);
            delete task;
            Debug("finish a Task.");
        }
    }
}
