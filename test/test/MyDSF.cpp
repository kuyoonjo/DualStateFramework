//
//  MyDSF.cpp
//  DSFExample
//
//  Created by Yu Chen on 10/17/14.
//  Copyright (c) 2014 Yu Chen. All rights reserved.
//

#include "MyDSF.h"
#include "MySyncObj.h"
#include <dsf/TaskArgument.h>

MyDSF::MyDSF()
: dsf::DualStateFramework::DualStateFramework()
{
    this->initialize();
}
MyDSF::~MyDSF()
{
    delete this->printInt;
}

void MyDSF::initialize()
{
    this->printInt = new dsf::TaskFunction( [this](dsf::SynchronizedObject* to, dsf::SynchronizedObject* from, dsf::TaskArguments *args)
    {
        this->foo(from, args);
    });
}

void MyDSF::foo(dsf::SynchronizedObject* from, dsf::TaskArguments *args)
{
    dsf::TaskArgument myInt = args->at(0);
    int i;
    try {
        i = myInt.to<int>();
    } catch (yc::Exception::AnyException yea) {
        std::cout << yea.details() << std::endl;
    }
    std::cout << i << std::endl;
    i --;
    if (i < 0) {
        this->remove(from);
        return;
    }
    
    dsf::TaskArguments* tas = new dsf::TaskArguments();
    tas->push_back(i);
    this->send(from, from, this->printInt, tas);
}

void MyDSF::run()
{
    dsf::DualStateFramework::run();
}
