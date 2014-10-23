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
#include "Debug.h"

namespace dsf
{
    class DSF_API TaskBox : public Runnable
    {
    public:
        TaskBox();
        TaskBox(std::string name);
        virtual ~TaskBox();
        bool isEmpty();
        void push(Task* task);
        Task* pop();
        void start();
        std::vector<Task*>* tasks;
    private:
        std::string name;
        TaskBox* next;
    protected:
        virtual void run() override;        
    };
}
#endif
