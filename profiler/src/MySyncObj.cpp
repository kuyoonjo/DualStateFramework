//
//  MySyncObj.cpp
//  profiler
//
//  Created by Yu Chen on 2/8/15.
//
//

#include "../include/MySyncObj.h"

MySyncObj::MySyncObj()  : dsf::SynchronizedObject::SynchronizedObject()
{
}

void MySyncObj::run()
{
    if(this->receive())
        this->process();
}
