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
#include "Export.h"

namespace dsf
{
    /*! The class can lock the objects using an unspecified sequence of calls to their members lock and unlock that ensures that all arguments are locked on return (without producing any deadlocks).
     
     * Example.
     @code
     
     dsf->lock();
     dsf->drawables->push_back(syncObj); //the object drawables is locked
     dsf->unlock();
     
     @endcode
     */
	class DSF_API Lock
    {
    protected:
        tbb::mutex locker;
    public:
        /*! \brief Locks all the objects passed as arguments, blocking the calling thread if necessary.
         */
        void lock();
        /*! \brief Unlocks all the objects.
         */
        void unlock();
    };
}

#endif
