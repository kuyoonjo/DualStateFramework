//
//  MySyncObj.h
//  DSFExample
//
//  Created by Yu Chen on 11/5/14.
//  Copyright (c) 2014 Yu Chen. All rights reserved.
//

#ifndef __DSFExample__MySyncObj__
#define __DSFExample__MySyncObj__

#include <dsf/SynchronizedObject.h>

class MySyncObj : public dsf::SynchronizedObject
{
public:
    MySyncObj() : dsf::SynchronizedObject::SynchronizedObject(){}
protected:
    void run() override;
};

#endif /* defined(__DSFExample__MySyncObj__) */
