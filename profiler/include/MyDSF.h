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
#include "ResourcePath.hpp"

class MyDSF : public dsf::DualStateFramework, public dsf::sfml::RenderWindow, public dsf::Lock
{
private:
    class Sender;
    FPS* fps;
    std::vector<std::tuple<float,float,float>> fpsList;
    sf::Clock* clock;
    sf::Font font;
    unsigned int numberOfCores = 1;
    std::vector<std::tuple<float,float,float>> stretch(std::vector<std::tuple<float,float,float>> arr,
                                                       std::vector<std::tuple<float,float,float>> strelen,
                                                       int maxLen);
public:
    MyDSF();
    ~MyDSF();
    void initialize() override;
    Sender* sender;
    unsigned int duration = 10;
    unsigned int maxNumberOfCores = 8;
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
