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
        
        /*! \brief For Signing TaskFunction Pointers
         *
         * Example.
         @code
         void MyDSF::initialize()
         {
            this->printInt = [this](dsf::TaskArguments *args)
                            {
                                this->foo(args);
                            };
         }
         
         void MyDSF::foo(dsf::TaskArguments *args)
         {
            dsf::TaskArgument* arg = args->front();
            int* i = arg->getValue<int>();
            std::cout<< *i << std::endl;
         }
         @endcode
         */
        virtual void initialize() = 0;
        
        /*! \brief Start all SyncronizedObjects associated.
         *          Keep looping.
         */
        void start();
        
        /*! \brief Start all SyncronizedObjects associated.
         */
        void doOneFrame();
        
        /*! \brief Add a SynchronizedObject.
         */
        void add(SynchronizedObject* syncObj);
    private:
        std::vector<SynchronizedObject*>* syncObjs;
    protected:
        /*! \brief Start all SyncronizedObjects associated.
        */
         virtual void run() override;
    };
}

#endif
