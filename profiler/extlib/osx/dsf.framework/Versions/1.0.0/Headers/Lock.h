//
//  Lockable.h
//  dsf
//
//  Created by Yu Chen on 12/10/14.
//
//

#ifndef dsf_Lock_h
#define dsf_Lock_h

#include <mutex>

namespace dsf
{
    class Lock
    {
    protected:
        std::mutex locker;
        void lock();
        void unlock();
    };
}

#endif
