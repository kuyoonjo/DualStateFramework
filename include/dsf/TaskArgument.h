//
//  TaskArguments.h
//  dsf
//
//  Created by Yu Chen on 10/17/14.
//
//

#ifndef dsf_TaskArgument_h
#define dsf_TaskArgument_h

#include <vector>

namespace dsf
{
    class TaskArgument
    {
    public:
        template <class T> static TaskArgument* parse(T* t);
        template <class T> T* getValue();
        template <class T> void setValue(T* t);
    private:
        void* value;
    };

    typedef std::vector<dsf::TaskArgument*> TaskArguments;
}

namespace dsf {
    template <class T> TaskArgument* TaskArgument::parse(T* t)
    {
        TaskArgument* taskArgument = new TaskArgument();
        taskArgument->setValue(t);
        return taskArgument;
    }
    template <class T> T* TaskArgument::getValue()
    {
        return static_cast<T*>(value);
    }
    template <class T> void TaskArgument::setValue(T *t)
    {
        this->value = t;
    }
}


#endif
