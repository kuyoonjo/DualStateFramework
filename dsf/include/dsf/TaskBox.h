//
//  Parallelable.h
//  DSF
//
//  Created by Yu Chen on 10/14/14.
//
//

#ifndef dsf_TaskBox_h
#define dsf_TaskBox_h

#include <vector>
#include <string>

#include "Export.h"
#include "Declaration.h"
#include "Task.h"
#include "Runnable.h"

namespace dsf
{
    /*! \brief A dsf::Task queue.
     * \details The dsf::TaskBox contains a list of def::Task objects. It provides essential methods to control the list such as “push”, “pop”, and “isEmpty”.
     */
    class DSF_API TaskBox
    {
    public:
        TaskBox();
        virtual ~TaskBox();
        /*! Checks wheather the queue is empty or not. */
        bool isEmpty();
        /*! Pushes a task into the queue. */
        void push(Task* task);
        /*! Pops out a task and returns it */
        Task* pop();
        /*! Pops out all tasks in the queue and executes them. */
        void process();
    protected:
        /*! The list of dsf::Task. */
        std::vector<Task*>* tasks;
    };
}
#endif
