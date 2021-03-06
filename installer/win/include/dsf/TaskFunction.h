//
//  TaskFunction.h
//  dsf
//
//  Created by Yu Chen on 10/17/14.
//
//

#ifndef dsf_TaskFunction_h
#define dsf_TaskFunction_h

#include <functional>
#include <vector>

#include "TaskArgument.h"

namespace dsf
{
    typedef std::function<void (dsf::SynchronizedObject*, dsf::SynchronizedObject*, TaskArgument*)> TaskFunction;
    typedef void function;
}

#endif
