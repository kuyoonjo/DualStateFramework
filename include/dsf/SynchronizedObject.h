//
//  SynchronizedObject.h
//  dsf
//
//  Created by Yu Chen on 10/17/14.
//
//

#ifndef dsf_SynchronizedObject_h
#define dsf_SynchronizedObject_h

#include <vector>
#include <string>

#include "Export.h"
#include "Task.h"
#include "TaskBox.h"
#include "TaskFunction.h"
#include "TaskArgument.h"
#include "Runnable.h"
#include "Debug.h"

namespace dsf
{
    /**
     * Class SynchronizedObject
     */
    
    class DSF_API SynchronizedObject : public Runnable, public TaskBox
    {
    public:
        SynchronizedObject();
        virtual ~SynchronizedObject();
        void send(SynchronizedObject* to,
                  TaskFunction* taskFunction,
                  TaskArguments* args);
        void start();
    protected:
        virtual void run() override = 0;
        
    };
}

#endif
