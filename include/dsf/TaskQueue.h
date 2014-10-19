//
//  TaskQueue.h
//  dsf
//
//  Created by Yu Chen on 10/17/14.
//
//

#ifndef dsf_TaskQueue_h
#define dsf_TaskQueue_h

#include <vector>

#include "Export.h"
#include "TaskBox.h"
#include "TaskFunction.h"
#include "TaskArgument.h"

namespace dsf
{
    /**
     * Class TaskQueue
     */
    
    class DSF_API TaskQueue
    {
    public:
        bool isEmpty();
        void processMessage();
        void sendMessage(TaskBox* to,
                         TaskBox* from,
                         TaskFunction taskFunction,
                         std::vector<TaskArgument*>* args);
    private:
        TaskBox* taskBox;
        TaskBox* nextTaskBox;
    protected:
        
    };
}

#endif
