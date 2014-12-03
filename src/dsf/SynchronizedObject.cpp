//
//  SynchronizedObject.cpp
//  dsf
//
//  Created by Yu Chen on 10/17/14.
//
//

#include <dsf/SynchronizedObject.h>

namespace dsf
{
    SynchronizedObject::SynchronizedObject()
    : TaskBox::TaskBox()
    {
        this->state = State::STOPPED;
        Debug("A SynchronizedObject Object has been created.");
    }
    SynchronizedObject::~SynchronizedObject()
    {
        Debug("A SynchronizedObject Object has been removed.");
    }
    
    SynchronizedObject::State SynchronizedObject::getState()
    {
        return this->state;
    }
    
    void SynchronizedObject::synchronize(dsf::SynchronizedVar &syncVar)
    {
        this->syncVars.push_back(&syncVar);
    }
    
    
    ////////////////////////////////////////////////////////
    // Privates
    ////////////////////////////////////////////////////////
    
    void SynchronizedObject::synchronize()
    {
        std::for_each(this->syncVars.begin(), this->syncVars.end(),
                      [](SynchronizedVar* syncVar)
                      {
                          syncVar->synchronize();
                      });
    }
    void SynchronizedObject::send(dsf::SynchronizedObject *to,
                                TaskFunction *taskFunction,
                                TaskArgument *args)
    {
        to->push(new Task(to, this, taskFunction, args));
    }
    
    
    void SynchronizedObject::start()
    {
        this->state = State::RUNNING;
        Debug("A SynchronizedObject is running");
        this->run();
        if(this->state == State::RUNNING)
            this->stop();
    }
    
    void SynchronizedObject::stop()
    {
        this->state = State::STOPPED;
        Debug("A SynchronizedObject is stopped.");
    }
    
    void SynchronizedObject::distroy()
    {
        this->state = State::DELETED;
        Debug("A SynchronizedObject is distroyed.");
    }
}