//
//  SyncCircle.cpp
//  profiler
//
//  Created by Yu Chen on 2/21/15.
//
//

#include "../include/SyncCircle.h"

SyncCircle::SyncCircle()  : dsf::SynchronizedObject::SynchronizedObject(), sf::CircleShape::CircleShape()
{
}

void SyncCircle::run()
{
    if(this->receive())
        this->process();
}