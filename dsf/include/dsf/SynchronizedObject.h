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
#include "Debug.h"

namespace dsf
{
    /*! The dsf::SynchronizedObject is a subclass of dsf::TaskBox. In this framework, you can regard it as thread. It provides methods for implementing parallelism such as “send”, “receive”, and etc.
     *
     * Example.
     @code
     // SyncCircle.h
     
     #include <dsf/SynchronizedObject.h>
     #include <SFML/Graphics.hpp>
     
     class SyncCircle : public dsf::SynchronizedObject, public sf::CircleShape
     {
     public:
        SyncCircle();
     protected:
        void run() override;
     };
     
     
     // SyncCircle.cpp
     
     #include "SyncCircle.h"
     
     SyncCircle::SyncCircle()  : dsf::SynchronizedObject::SynchronizedObject(), sf::CircleShape::CircleShape()
     {
     }
     
     void SyncCircle::run()
     {
        if(this->receive())
            this->process();
     }
     
     @endcode
     */
    class DSF_API SynchronizedObject : public Runnable, public TaskBox
    {
    public:
        SynchronizedObject();
        virtual ~SynchronizedObject();
        /*! \brief Returns the current state.
         */
        State getState() override;
    private:
        State state;
        
        void send(SynchronizedObject* to,
                  TaskFunction* taskFunction,
                  TaskArgument* args);
        void start();
        void stop();
        void distroy();
        friend class DualStateFramework;
    protected:
        virtual void run() override = 0;
        
    };
}

#endif
