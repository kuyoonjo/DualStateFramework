//
//  SynchronizedVar.h
//  dsf
//
//  Created by Yu Chen on 12/2/14.
//
//

#ifndef dsf_SynchronizedVar_h
#define dsf_SynchronizedVar_h

#include "Export.h"
#include <yctools/Any.h>
#include "Synchronisable.h"
#include "Lock.h"

namespace dsf
{
    /*! The purpose of this class is to make thread-safe variables for dsf::SynchronizedObject objects. A dsf::SynchronizedVar object has two member variables - “value” and “next”. The “value” is for read operation, and the “next” is for write operation. The function “synchronize” signs “next” to “value”. 
     *
     *Example
     @code
     dsf::SynchronizedVar myInt;
     myInt = int(8); // value == NULL, next == 8
     myInt.synchronize(); // value == 8, next == 8
     std::cout << myInt.to<int>() << std::endl; // output 8
     myInt = int(9); // value == 8, next == 9
     std::cout << myInt.to<int>() << std::endl; // output 8
     myInt.synchronize(); // value == 9, next == 9
     std::cout << myInt.to<int>() << std::endl; // output 9
     @endcode
     */
    class DSF_API SynchronizedVar : public Synchronisable<yc::Any>, public yc::Any, public Lock
    {
    public:
        template<typename T> SynchronizedVar(T && value);
        template<typename T> void operator=(T && value);
        void synchronise() override;
    };
}

namespace dsf
{
    
    template<typename T> SynchronizedVar::SynchronizedVar(T && value)
    : Any(value)
    {
        this->next = new Any(value);
    }
    
    template<typename T> void SynchronizedVar::operator=(T && value)
    {
        this->lock();
        this->next = value;
        this->unlock();
    }
}


#endif
