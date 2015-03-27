//
//  SyncCircle.cpp
//  profiler
//
//  Created by Yu Chen on 2/21/15.
//
//

#include "../include/SyncCircle.h"

SyncCircle::SyncCircle()  : SynchronizedObject(), CircleShape()
{
}

void SyncCircle::run()
{
    if(this->receive())
        this->process();
}