//
//  MyDSF.cpp
//  profiler
//
//  Created by Yu Chen on 2/8/15.
//
//

#include "../include/MyDSF.h"
#include "../include/MySyncObj.h"
#include <dsf/TaskArgument.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <yctools/Random.h>

MyDSF::MyDSF()
: dsf::DualStateFramework::DualStateFramework()
{
    this->initialize();
}
MyDSF::~MyDSF()
{
    delete this->createObj;
}

void MyDSF::initialize()
{
    this->createObj = new dsf::TaskFunction( [this](dsf::SynchronizedObject* to,
                                                    dsf::SynchronizedObject* from,
                                                    dsf::TaskArgument *args)
                                           {
                                               auto o = (MySyncObj*) to;
                                               o->shape = sf::CircleShape(2);
                                               o->shape.setFillColor(sf::Color::Cyan);
                                               o->shape.setPosition(yc::Random::randInt(1, 595),
                                                                 yc::Random::randInt(1, 495));
                                               this->remove(from);
                                           });
}

void MyDSF::run()
{
    dsf::DualStateFramework::run();
}

