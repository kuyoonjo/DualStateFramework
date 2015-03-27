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
		: TaskBox()
    {
        this->state = State::STOPPED;
    }
    SynchronizedObject::~SynchronizedObject()
    {
    }
    
    SynchronizedObject::State SynchronizedObject::getState()
    {
        return this->state;
    }

    
    
    ////////////////////////////////////////////////////////
    // Privates
    ////////////////////////////////////////////////////////
    
    void SynchronizedObject::send(dsf::SynchronizedObject *to,
                                TaskFunction *taskFunction,
                                TaskArgument *args)
    {
        to->push(new Task(to, this, taskFunction, args));
    }
    
    
    void SynchronizedObject::start()
    {
        this->state = State::RUNNING;
        this->run();
        if(this->state == State::RUNNING)
            this->stop();
    }
    
    void SynchronizedObject::stop()
    {
        this->state = State::STOPPED;
    }
    
    void SynchronizedObject::distroy()
    {
        this->state = State::DELETED;
    }
}