//
//  MySyncObj.h
//  profiler
//
//  Created by Yu Chen on 2/8/15.
//
//

#ifndef profiler_MySyncObj_h
#define profiler_MySyncObj_h

#include <dsf/SynchronizedObject.h>
#include <dsf/SynchronizedVar.h>
#include <SFML/Graphics.hpp>

class MySyncObj : public dsf::SynchronizedObject, public sf::CircleShape
{
public:
    MySyncObj();
protected:
    void run() override;
};

#endif
