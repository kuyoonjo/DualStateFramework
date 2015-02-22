//
//  Lockable.h
//  dsf
//
//  Created by Yu Chen on 12/10/14.
//
//

#ifndef dsf_Lock_h
#define dsf_Lock_h

#include <tbb/mutex.h>

namespace dsf
{
    class Lock
    {
    protected:
        tbb::mutex locker;
    public:
        void lock();
        void unlock();
    };
}

#endif
