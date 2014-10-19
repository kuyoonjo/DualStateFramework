//
//  TaskManager.cpp
//  dsf
//
//  Created by Yu Chen on 10/17/14.
//
//

#include <dsf/DualStateFramework.h>

namespace dsf
{
    DualStateFramework::DualStateFramework()
    {
        this->initialize();
    }
    DualStateFramework::~DualStateFramework()
    {
        while (!this->taskQueues->empty()) {
            TaskQueue* taskQueue = this->taskQueues->back();
            this->taskQueues->pop_back();
            delete taskQueue;
        }
        delete this->taskQueues;
    }
    void DualStateFramework::initialize()
    {
        this->taskQueues = new std::vector<TaskQueue*>();
    }
    void DualStateFramework::tidy()
    {
        
    }
    void DualStateFramework::start()
    {
        this->doOneFrame();
        for (std::vector<TaskQueue*>::iterator i = this->taskQueues->begin();
          i != this->taskQueues->end();
          ++i)
        {
            if ((*i)->isEmpty())
            {
                delete *i;
                this->taskQueues->erase(i);
            }
        }
        if (!this->taskQueues->empty()) {
            this->start();
        }
    }
    void DualStateFramework::doOneFrame()
    {
        this->run();
    }
    void DualStateFramework::run()
    {
        for (std::vector<TaskQueue*>::iterator i = this->taskQueues->begin();
             i != this->taskQueues->end();
             ++i)
        {
            (*i)->processMessage();
        }
    }
}