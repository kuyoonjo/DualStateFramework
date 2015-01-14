//
//  Lockable.h
//  dsf
//
//  Created by Yu Chen on 12/10/14.
//
//

#ifndef dsf_Lock_h
#define dsf_Lock_h

namespace dsf
{
    class Lock
    {
    protected:
        bool locked;
        void lock();
        void unlock();
    };
}

#endif
