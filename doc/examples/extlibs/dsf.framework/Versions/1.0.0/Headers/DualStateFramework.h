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
    /*! \brief The starting pointer for the framework is the abstract class dsf::DualStateFramework.
     * \details It provides essential functions for associating and managing its components (SynchronizedObject objects, function points, and etc.).
     * \section eg Example
     * \include MyDSF.h
     */
    class DSF_API DualStateFramework : public Runnable
    {
    public:
        DualStateFramework();
        
        ~DualStateFramework();
        
        /*! For Signing TaskFunction Pointers
         *
         * \section eg Example
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
        
        /*!  Start all SyncronizedObjects associated.
         */
        void start();
        
        /*!  Do one frame of all SyncronizedObjects.
         */
        void doOneFrame();
        
        
        
        /*!  Add a SynchronizedObject.
         */
        void add(SynchronizedObject* syncObj);
        
        /*!  Remove a SynchronizedObject.
         */
        void remove(SynchronizedObject* syncObj);
        
        /*!  Send messages
         */
        void send(SynchronizedObject* to,
                  SynchronizedObject* from,
                  TaskFunction* taskFunction,
                  TaskArgument* args);
        
        /*!  Return the state of the object.
         */
        State getState() override;
        
        /*! Set the number of threads.
         * 0 is automatic.
         */
        void setNumberOfThreads(int NumberOfThreads);
        
    private:
        int NumberOfThreads;
        std::vector<SynchronizedObject*>* syncObjs;
        State state;
    protected:
        /*!  Clear all SyncronizedObjects which is marked as DELETE
         */
        virtual void refresh();
        /*!  Start all SyncronizedObjects associated.
        */
         virtual void run() override;
    };
}

#endif
