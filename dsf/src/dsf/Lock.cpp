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
        this->locker.lock();
    }
    
    void Lock::unlock()
    {
        this->locker.unlock();
    }
}
