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
    
    TaskBox::TaskBox(std::string name)
    : TaskBox::TaskBox()
    {
        this->name = name;
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
    
    void TaskBox::start()
    {
        if (this->next)
        {
            if (this->next->isEmpty()) {
                delete this->next;
                return;
            }
            while (!this->next->isEmpty())
            {
                this->tasks->push_back(this->next->pop());
            }
            this->run();
        }
    }
    
    void TaskBox::run()
    {
        while (!this->isEmpty())
        {
            Debug("start a Task ...");
            Task* task = this->pop();
            (*task->taskFunction)(task->taskArguments);
        }
    }
}
