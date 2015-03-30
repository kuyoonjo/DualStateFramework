//
//  SynchronizedVar.cpp
//  dsf
//
//  Created by Yu Chen on 12/2/14.
//
//

#include <dsf/SynchronizedVar.h>

namespace dsf
{
    void SynchronizedVar::synchronise()
    {
        *((yc::Any*)this) = *this->next;
    }
}

