#ifndef __DSFExample__MyDSF__
#define __DSFExample__MyDSF__

#include <dsf/DualStateFramework.h>

class MyDSF : public dsf::DualStateFramework // Extends dsf::DualStateFramework
{
public:
    explicit MyDSF() : DualStateFramework() {} // Uses default super constructor
    void initialize() override {}
};

#endif
