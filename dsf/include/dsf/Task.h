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


namespace dsf
{
    /*! \brief Class Task.
     * \details This class have four members: from, to, function, and arguments, where "from" is a dsf::SynchronizedObject object who sent message to you.
     */
    
    class DSF_API Task
    {
    public:
        /*! Where the message is sent to. */
        SynchronizedObject* to;
        /*! Where the message is sent from. */
        SynchronizedObject* from;
        /*! The function pointer. */
        TaskFunction* taskFunction;
        /*! The arguments for the function pointer. */
        TaskArgument* taskArgument;
        explicit Task(SynchronizedObject* to,
             SynchronizedObject* from,
             TaskFunction* taskFunction,
             TaskArgument* taskArgument);
        ~Task();
    };
}

#endif
