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
#include "Export.h"

namespace dsf
{
    /*! \brief Locking variables
     * \details The class can lock the objects using an unspecified sequence of calls to their members lock and unlock that ensures that all arguments are locked on return (without producing any deadlocks).
     
     * \section eg Example
     @code
     
     dsf->lock();
     dsf->drawables->push_back(syncObj); //the object drawables is locked
     dsf->unlock();
     
     @endcode
     */
	class DSF_API Lock
    {
    protected:
        /*! The locker */
        std::mutex locker;
    public:
        /*! Locks all the objects passed as arguments, blocking the calling thread if necessary. */
        void lock();
        /*! Unlocks all the objects. */
        void unlock();
    };
}

#endif
