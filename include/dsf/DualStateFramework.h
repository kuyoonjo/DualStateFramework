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
#include "SynchronizedObject.h"
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
        void add(SynchronizedObject* syncObj);
    private:
        std::vector<SynchronizedObject*>* syncObjs;
    protected:
        /**
         * 
         */
        virtual void initialize() = 0;
        virtual void run() override;
    };
}

#endif
