//
//  DSFSFMLOBJ.h
//  profiler
//
//  Created by Yu Chen on 2/17/15.
//
//

#ifndef profiler_DSFSFMLOBJ_h
#define profiler_DSFSFMLOBJ_h

#include <dsf/DualStateFramework.h>
#include <dsf/SynchronizedObject.h>
#include <dsf/TaskFunction.h>
#include <SFML/Graphics.hpp>

class DSFSFMLOBJ : public dsf::SynchronizedObject
{
public:
    DSFSFMLOBJ();
    ~DSFSFMLOBJ();
    dsf::TaskFunction* Create;
    dsf::TaskFunction* Update;
protected:
    virtual dsf::function create(dsf::SynchronizedObject* to,
                         dsf::SynchronizedObject* from,
                         dsf::TaskArgument* args) = 0;
    virtual dsf::function update(dsf::SynchronizedObject* to,
                         dsf::SynchronizedObject* from,
                         dsf::TaskArgument* args) = 0;
    virtual dsf::function destroy(dsf::SynchronizedObject* to,
                          dsf::SynchronizedObject* from,
                          dsf::TaskArgument* args) = 0;
    virtual void run() override = 0;
};

#endif
