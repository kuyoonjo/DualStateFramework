//
//  TaskArguments.h
//  dsf
//
//  Created by Yu Chen on 10/17/14.
//
//

#ifndef dsf_TaskArgument_h
#define dsf_TaskArgument_h

#include <memory>
#include <vector>

namespace dsf
{
    class TaskArgument
    {
    public:
        template <class T> static TaskArgument* parse(T* t);
        template <class T> T* to();
        template <class T> void setValue(T* t);
    private:
        std::shared_ptr<void> value;
    };
    typedef std::vector<TaskArgument*> TaskArguments;
}

namespace dsf {
    template <class T> TaskArgument* TaskArgument::parse(T* t)
    {
        TaskArgument* taskArgument = new TaskArgument();
        taskArgument->setValue(t);
        return taskArgument;
    }
    template <class T> T* TaskArgument::to()
    {
        return std::static_pointer_cast<T>(value).get();
    }
    template <class T> void TaskArgument::setValue(T *t)
    {
        this->value = std::shared_ptr<T>(t);
    }
}




#endif
