//
//  SynchronizedVar.h
//  dsf
//
//  Created by Yu Chen on 12/2/14.
//
//

#ifndef dsf_SynchronizedVar_h
#define dsf_SynchronizedVar_h

#include <yctools/Any.h>
#include "Lock.h"

namespace dsf
{
    class SynchronizedVar : public Lock
    {
    public:
        SynchronizedVar();
        template<typename T> SynchronizedVar(T && value);
        template<typename T> void operator=(T && value);
        template<typename T> T to();
        void synchronize();
        
    protected:
        template<typename T> void set(T && value);
        
    private:
        yc::Any value;
        yc::Any next;
    };
}

namespace dsf
{
    
    template<typename T> SynchronizedVar::SynchronizedVar(T && value)
    : next(value)
    {}
    
    template<typename T> T SynchronizedVar::to()
    {
        return value.to<T>();
    }
    
    template<typename T> void SynchronizedVar::operator=(T && value)
    {
        this->set(value);
    }
    
    template<typename T> void SynchronizedVar::set(T && value)
    {
        this->lock();
        this->next = value;
        this->unlock();
    }
}


#endif
