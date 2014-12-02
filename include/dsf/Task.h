//
//  Parallel.h
//  DualStateFramework
//
//  Created by Yu Chen on 10/13/14.
//  Copyright (c) 2014 Yu Chen. All rights reserved.
//

#ifndef dsf_Task_h
#define dsf_Task_h

#include <vector>
#include <memory>

#include "Export.h"
#include "Declaration.h"
#include "TaskBox.h"
#include "TaskFunction.h"
#include "TaskArgument.h"
#include "Debug.h"


namespace dsf
{
    /**
     * Class Task
     */
    
    class DSF_API Task
    {
    public:
        SynchronizedObject* to;
        SynchronizedObject* from;
        TaskFunction* taskFunction;
        TaskArguments* taskArguments;
        Task();
        Task(SynchronizedObject* to, SynchronizedObject* from, TaskFunction* taskFunction, TaskArguments* taskArguments);
        ~Task();
    };
}

#endif
