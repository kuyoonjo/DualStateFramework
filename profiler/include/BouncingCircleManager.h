//
//  BouncingCircleManager.h
//  profiler
//
//  Created by Yu Chen on 2/22/15.
//
//

#ifndef profiler_BouncingCircleManager_h
#define profiler_BouncingCircleManager_h

#include "MyDSF.h"
#include "SyncBouncingCircle.h"
#include <yctools/Random.h>
#include <vector>

class BouncingCircleManager
{
public:
    BouncingCircleManager(MyDSF* dsf);
    ~BouncingCircleManager();
    MyDSF* dsf;
    dsf::TaskFunction* create;
    dsf::TaskFunction* update;
    dsf::TaskFunction* destroy;
    std::vector<SyncBouncingCircle*>* createRandomCircles(int number, int radius, int boundX, int boundY);
private:
    SyncBouncingCircle* createRandomCircle(int radius, int boundX, int boundY);
};


#endif
