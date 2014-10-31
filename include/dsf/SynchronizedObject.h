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
    
    class DSF_API SynchronizedObject : public Runnable
    {
    public:
        SynchronizedObject();
        virtual ~SynchronizedObject();
        bool isEmpty();
        void process(unsigned int index);
        void sendMessage(TaskBox* to,
                         TaskBox* from,
                         TaskFunction* taskFunction,
                         TaskArguments* args);
        void add(TaskBox* taskBox);
        void remove(std::string name);
        void start();
    private:
        std::vector<TaskBox*>* taskBoxes;
    protected:
        virtual void run() override;
        
    };
}

#endif
