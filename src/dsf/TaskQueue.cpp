//
//  TaskQueue.cpp
//  dsf
//
//  Created by Yu Chen on 10/17/14.
//
//

#include <dsf/TaskQueue.h>

namespace dsf
{
    bool TaskQueue::isEmpty()
    {
        return this->taskBox->isEmpty();
    }
    void TaskQueue::processMessage()
    {
        while (!this->taskBox->isEmpty()) {
            Task* task = this->taskBox->pop();
            task->taskFunction(task->taskArguments);
        }
    }
}