//
//  TaskManager.cpp
//  dsf
//
//  Created by Yu Chen on 10/17/14.
//
//

#include <tbb/parallel_for_each.h>
#include <dsf/DualStateFramework.h>
#include <tbb/task_scheduler_init.h>

namespace dsf
{
    DualStateFramework::DualStateFramework()
    {
        this->NumberOfThreads = tbb::task_scheduler_init::automatic;
        this->syncObjs = new std::vector<SynchronizedObject*>();
        this->state = DualStateFramework::State::STOPPED;
        Debug("A DSF Object has been created.");
    }
    
    DualStateFramework::~DualStateFramework()
    {
        while (!this->syncObjs->empty()) {
            SynchronizedObject* syncObj = this->syncObjs->back();
            this->syncObjs->pop_back();
            delete syncObj;
        }
        delete this->syncObjs;
        Debug("A DSF Object has been removed.");
    }
    
    void DualStateFramework::start()
    {
        if(!this->syncObjs->empty())
        {
            this->doOneFrame();
            this->start();
        }
    }
    
    void DualStateFramework::doOneFrame()
    {
        this->refresh();
        
        if(!this->syncObjs->empty())
        {
            this->state = DualStateFramework::State::RUNNING;
            this->run();
            if(this->state == DualStateFramework::State::RUNNING)
                this->state = DualStateFramework::State::STOPPED;
        }
    }
    
    
    void DualStateFramework::add(dsf::SynchronizedObject *syncObj)
    {
        this->syncObjs->push_back(syncObj);
    }
    
    void DualStateFramework::remove(dsf::SynchronizedObject *syncObj)
    {
        syncObj->distroy();
    }
    
    void DualStateFramework::send(dsf::SynchronizedObject *to, dsf::SynchronizedObject *from, TaskFunction *taskFunction, TaskArgument *args)
    {
        from->send(to, taskFunction, args);
    }
    
    DualStateFramework::State DualStateFramework::getState()
    {
        return this->state;
    }
    
    void DualStateFramework::setNumberOfThreads(int NumberOfThreads)
    {
        if(NumberOfThreads == 0)
            this->NumberOfThreads = tbb::task_scheduler_init::automatic;
        else
            this->NumberOfThreads = NumberOfThreads;
    }
    
    //////////////////////////////////////////////////////////////////
    // Private
    //////////////////////////////////////////////////////////////////
    
    void DualStateFramework::refresh()
    {
        this->syncObjs->erase(std::remove_if(this->syncObjs->begin(),
                                             this->syncObjs->end(),
                                             [](SynchronizedObject* sb)
                                             {
                                                 if (sb->getState() == SynchronizedObject::State::DELETED) {
                                                     delete sb;
                                                     return true;
                                                 }
                                                 sb->synchronize();
                                                 return false;
                                             }) ,
                              this->syncObjs->end());
    }
    
    //////////////////////////////////////////////////////////////////
    // Protected
    //////////////////////////////////////////////////////////////////

    
    void DualStateFramework::run()
    {
        tbb::task_scheduler_init init(this->NumberOfThreads);
        tbb::parallel_for_each(this->syncObjs->begin(),
                               this->syncObjs->end(),
                               [](SynchronizedObject* sb)
                               {
                                   if(sb->getState() == SynchronizedObject::State::STOPPED)
                                   {
                                       sb->synchronize();
                                       sb->start();
                                   }
                               });
    }
}