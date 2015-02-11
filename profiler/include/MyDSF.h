//
//  MyDSF.h
//  profiler
//
//  Created by Yu Chen on 2/8/15.
//
//

#ifndef profiler_MyDSF_h
#define profiler_MyDSF_h

#include <dsf/DualStateFramework.h>
#include <dsf/TaskFunction.h>

class MyDSF : public dsf::DualStateFramework
{
public:
    MyDSF();
    ~MyDSF();
    void initialize() override;
    dsf::TaskFunction* createObj;
private:
protected:
    void run() override;
};


#endif
