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
        template <class T> T* getValue();
        template <class T> void setValue(T* t);
    private:
        void* value;
    };
}

namespace dsf {
    template <class T> T* TaskArgument::getValue()
    {
        return static_cast<T*>(value);
    }
    template <class T> void TaskArgument::setValue(T *t)
    {
        this->value = t;
    }
}

typedef std::vector<dsf::TaskArgument*> TaskArguments;

#endif
