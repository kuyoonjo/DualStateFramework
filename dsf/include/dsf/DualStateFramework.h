//
//  DualStateFramework.h
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

namespace dsf {
    /*! The starting pointer for the framework is the abstract class def::DualStateFramework. It provides essential functions for associating and managing its components (SynchronizedObject objects, function points, and etc.). 
     *
     * Example.
     @code
     #include <dsf/DualStateFramework.h>
     
     class MyDSF : public dsf::DualStateFramework
     {
     public:
         MyDSF();
         ~MyDSF();
         void initialize() override;
     protected:
         void refresh() override;
         void run() override;
     };
     
     @endcode
     */
    class DSF_API DualStateFramework : public Runnable
    {
    public:
        DualStateFramework();
        
        ~DualStateFramework();
        
        /*! \brief For Signing TaskFunction Pointers
         *
         * Example.
         @code
         this->printHello = new dsf::TaskFunction([this](dsf::SynchronizedObject* to,
                                                         dsf::SynchronizedObject* from,
                                                         dsf::TaskArgument* args)
         {
            std::string str;
            float f;
            std::tie(str, f) = args->to<std::tuple<std::string, float>>();
            std::cout << str << " " << f << std::endl;
            this->remove(from);
         });

         @endcode
         */
        virtual void initialize() = 0;
        
        /*! \brief Start all SyncronizedObjects associated.
         */
        void start();
        
        /*! \brief Do one frame of all SyncronizedObjects.
         */
        void doOneFrame();
        
        
        
        /*! \brief Add a SynchronizedObject.
         */
        void add(SynchronizedObject* syncObj);
        
        /*! \brief Remove a SynchronizedObject.
         */
        void remove(SynchronizedObject* syncObj);
        
        /*! \brief Send messages
         */
        void send(SynchronizedObject* to,
                  SynchronizedObject* from,
                  TaskFunction* taskFunction,
                  TaskArgument* args);
        
        /*! \brief Return the state of the object.
         */
        State getState() override;
        
        /*! \brief Set the number of threads.
         * 0 is automatic.
         */
        void setNumberOfThreads(int NumberOfThreads);
        
    private:
        int NumberOfThreads;
        std::vector<SynchronizedObject*>* syncObjs;
        State state;
    protected:
        /*! \brief Clear all SyncronizedObjects which is marked as DELETE
         */
        virtual void refresh();
        /*! \brief Start all SyncronizedObjects associated.
        */
         virtual void run() override;
    };
}

#endif
