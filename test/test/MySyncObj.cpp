//
//  MySyncObj.cpp
//  DSFExample
//
//  Created by Yu Chen on 11/5/14.
//  Copyright (c) 2014 Yu Chen. All rights reserved.
//

#include "MySyncObj.h"

void MySyncObj::run()
{
    this->receive();
    this->process();
}