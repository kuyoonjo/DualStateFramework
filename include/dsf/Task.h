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

#include "Export.h"
#include "Declaration.h"
#include "TaskBox.h"
#include "TaskFunction.h"
#include "TaskArgument.h"


namespace dsf
{
    /**
     * Class Task
     */
    
    class DSF_API Task
    {
    public:
        TaskBox* from;
        TaskFunction taskFunction;
        std::vector<TaskArgument*>* taskArguments;
    };
}

#endif
