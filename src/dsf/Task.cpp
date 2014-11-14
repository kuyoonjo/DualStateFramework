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
    Task::Task()
    {
        Debug("A Task has been created.");
    }
    
    Task::Task(SynchronizedObject* from,
               TaskFunction* taskFunction,
               TaskArguments* taskArguments)
    : Task::Task()
    {
        this->from = from;
        this->taskFunction = taskFunction;
        this->taskArguments = taskArguments;
    }
    
    Task::~Task()
    {
        delete this->taskArguments;
        Debug("A Task has been removed.");
    }
}