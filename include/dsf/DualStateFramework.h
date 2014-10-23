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
#include "Debug.h"

namespace dsf {
    class DSF_API DualStateFramework : public Runnable
    {
    public:
        DualStateFramework();
        ~DualStateFramework();
        void tidy();
        void start();
        void doOneFrame();
        void add(TaskQueue* taskQueue);
    private:
        std::vector<TaskQueue*>* taskQueues;
    protected:
        virtual void initialize();
        virtual void run() override;
    };
}

#endif
