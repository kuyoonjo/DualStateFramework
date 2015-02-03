//
//  Lock.cpp
//  dsf
//
//  Created by Yu Chen on 12/10/14.
//
//

#include <dsf/Lock.h>

namespace dsf
{
    void Lock::lock()
    {
        if (!this->locked)
            this->locked = true;
        else
            this->lock();
    }
    
    void Lock::unlock()
    {
        if(this->locked)
            this->locked = false;
        else
            this->unlock();
    }
}
