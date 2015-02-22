//
//  RandomCircleManager.h
//  profiler
//
//  Created by Yu Chen on 2/21/15.
//
//

#ifndef profiler_RandomCircleManager_h
#define profiler_RandomCircleManager_h

#include "MyDSF.h"
#include "SyncCircle.h"
#include <yctools/Random.h>

class RandomCircleManager
{
public:
    RandomCircleManager(MyDSF* dsf);
    ~RandomCircleManager();
    MyDSF* dsf;
    dsf::TaskFunction* create;
    dsf::TaskFunction* update;
    dsf::TaskFunction* destroy;
};

#endif
