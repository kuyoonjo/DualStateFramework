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
#include <dsf/Lock.h>
#include "DSFSFML.h"
#include "FPS.h"

class MyDSF : public dsf::DualStateFramework, public dsf::sfml::RenderWindow, public dsf::Lock
{
private:
    class Sender;
public:
    MyDSF();
    ~MyDSF();
    void initialize() override;
    Sender* sender;
    FPS* fps;
protected:
    void refresh() override;
    void run() override;
    void draw() override;
};

class MyDSF::Sender : public dsf::SynchronizedObject
{
public:
    Sender(dsf::DualStateFramework* dsf);
    ~Sender();
    dsf::DualStateFramework* dsf;
    dsf::TaskFunction* create;
    dsf::TaskFunction* update;
    dsf::TaskFunction* destroy;
protected:
    void run() override;
};


#endif
