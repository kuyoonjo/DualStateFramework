//
//  TaskManager.h
//  dsf
//
//  Created by Yu Chen on 10/17/14.
//
//

#ifndef dsf_DualStateFramework_h
#define dsf_DualStateFramework_h

#include <vector>

#include "TaskBox.h"
#include "Task.h"
#include "TaskQueue.h"
#include "Runnable.h"

namespace dsf {
    class DSF_API DualStateFramework : public Runnable
    {
    public:
        std::vector<TaskQueue*>* taskQueues;
        DualStateFramework();
        ~DualStateFramework();
        virtual void initialize();
        void tidy();
        void start();
        void doOneFrame();
    protected:
        virtual void run() override;
    };
}

#endif
