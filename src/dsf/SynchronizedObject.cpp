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
        this->run();
    }
    
}