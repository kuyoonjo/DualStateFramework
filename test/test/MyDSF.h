//
//  MyDSF.h
//  DSFExample
//
//  Created by Yu Chen on 10/17/14.
//  Copyright (c) 2014 Yu Chen. All rights reserved.
//

#ifndef __DSFExample__MyDSF__
#define __DSFExample__MyDSF__

#include <iostream>
#include <dsf/DualStateFramework.h>
#include <dsf/TaskFunction.h>
#include <dsf/TaskArgument.h>
#include <dsf/SynchronizedObject.h>
#include <dsf/TaskBox.h>

class MyDSF : public dsf::DualStateFramework
{
public:
    MyDSF();
    ~MyDSF();
    void initialize() override;
    dsf::TaskFunction* printInt;
private:
    int cout = 5;
protected:
    dsf::function foo(dsf::SynchronizedObject* from, dsf::TaskArguments* args);
    void run() override;
};


#endif /* defined(__DSFExample__MyDSF__) */
