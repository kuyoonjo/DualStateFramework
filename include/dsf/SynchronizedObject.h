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
#include "Declaration.h"
#include "Task.h"
#include "TaskBox.h"
#include "TaskFunction.h"
#include "TaskArgument.h"
#include "Runnable.h"
#include "SynchronizedVar.h"
#include "Debug.h"

namespace dsf
{
    class DSF_API SynchronizedObject : public Runnable, public TaskBox
    {
    public:
        SynchronizedObject();
        virtual ~SynchronizedObject();
        State getState() override;
        void synchronize(SynchronizedVar& syncVar);
    private:
        State state;
        std::vector<SynchronizedVar*> syncVars;
        
        
        void synchronize();
        void send(SynchronizedObject* to,
                  TaskFunction* taskFunction,
                  TaskArguments* args);
        void start();
        void stop();
        void distroy();
        friend class DualStateFramework;
    protected:
        virtual void run() override = 0;
        
    };
}

#endif
