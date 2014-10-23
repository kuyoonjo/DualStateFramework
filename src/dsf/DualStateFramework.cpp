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
        this->taskQueues = new std::vector<TaskQueue*>();
        this->initialize();
        Debug("A DSF Object has been created.");
    }
    
    DualStateFramework::~DualStateFramework()
    {
        while (!this->taskQueues->empty()) {
            TaskQueue* taskQueue = this->taskQueues->back();
            this->taskQueues->pop_back();
            delete taskQueue;
        }
        delete this->taskQueues;
        Debug("A DSF Object has been removed.");
    }
    
    
    void DualStateFramework::tidy()
    {
        
    }
    void DualStateFramework::start()
    {
        this->doOneFrame();
        this->taskQueues->erase(std::remove_if(this->taskQueues->begin(),
                                               this->taskQueues->end(),
                                               [](TaskQueue* tq)
                                                    {
                                                        if (tq->isEmpty()) {
                                                            delete tq;
                                                            return true;
                                                        }
                                                        return false;
                                                    }) ,
                                this->taskQueues->end());
        if (!this->taskQueues->empty()) {
            this->start();
        }
    }
    void DualStateFramework::doOneFrame()
    {
        this->run();
    }
    
    void DualStateFramework::add(dsf::TaskQueue *taskQueue)
    {
        this->taskQueues->push_back(taskQueue);
    }
    
    //////////////////////////////////////////////////////////////////
    // Protected
    //////////////////////////////////////////////////////////////////
    void DualStateFramework::initialize()
    {
    }
    
    void DualStateFramework::run()
    {
        for (auto i = this->taskQueues->begin();
             i != this->taskQueues->end();
             ++i)
        {
            (*i)->start();
        }
    }
}