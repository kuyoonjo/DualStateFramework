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
    
    void SynchronizedObject::send(dsf::SynchronizedObject *to,
                                TaskFunction *taskFunction,
                                TaskArguments *args)
    {
        to->push(new Task(this, taskFunction, args));
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
    
    SynchronizedObject::State SynchronizedObject::getState()
    {
        return this->state;
    }
}