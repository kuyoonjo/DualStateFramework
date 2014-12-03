//
//  Parallel.cpp
//  DualStateFramework
//
//  Created by Yu Chen on 10/13/14.
//  Copyright (c) 2014 Yu Chen. All rights reserved.
//

#include <dsf/Task.h>
namespace dsf
{
    Task::Task(SynchronizedObject* to,
               SynchronizedObject* from,
               TaskFunction* taskFunction,
               TaskArgument* taskArgument)
    {
        this->to = to;
        this->from = from;
        this->taskFunction = taskFunction;
        this->taskArgument = taskArgument;
    }
    
    Task::~Task()
    {
        delete this->taskArgument;
    }
}