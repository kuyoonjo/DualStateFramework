//
//  SyncCircle.h
//  profiler
//
//  Created by Yu Chen on 2/21/15.
//
//

#ifndef profiler_SyncCircle_h
#define profiler_SyncCircle_h

#include <dsf/SynchronizedObject.h>
#include <SFML/Graphics.hpp>

class SyncCircle : public dsf::SynchronizedObject, public sf::CircleShape
{
public:
    SyncCircle();
protected:
    void run() override;
};

#endif
