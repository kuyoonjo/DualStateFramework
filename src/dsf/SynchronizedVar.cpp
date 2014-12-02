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
    SynchronizedVar::SynchronizedVar()
    {
        // do nothing
    }
    void SynchronizedVar::synchronize()
    {
        this->value = this->next;
    }
}

