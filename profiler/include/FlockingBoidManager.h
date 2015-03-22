//
//  FlockingBoidManager.h
//  profiler
//
//  Created by Yu Chen on 3/12/15.
//
//

#ifndef profiler_FlockingBoidManager_h
#define profiler_FlockingBoidManager_h

#include "MyDSF.h"
#include "SyncFlockingBoid.h"
#include <yctools/Random.h>
#include <vector>

class FlockingBoidManager
{
public:
    FlockingBoidManager(MyDSF* dsf);
    ~FlockingBoidManager();
    MyDSF* dsf;
    dsf::TaskFunction* create;
    dsf::TaskFunction* update;
    dsf::TaskFunction* destroy;
};

#endif
