//
//  FPS.cpp
//  profiler
//
//  Created by Yu Chen on 2/8/15.
//
//

#include "../include/FPS.h"

FPS::FPS(float refreshTime)
{
    this->refreshTime = refreshTime;
}

FPS::~FPS()
{
    
}

float FPS::getFPS()
{
    if(this->fps == 0)
        this->fps = 1.0f / this->clockFps.getElapsedTime().asSeconds();
    return this->fps;
}

void FPS::refresh()
{
    if(this->average == 0)
        this->average = 1.0f / this->clockFps.getElapsedTime().asSeconds();
    else
        this->average = (this->average + 1.0f / this->clockFps.getElapsedTime().asSeconds()) / 2.0f;
    this->clockFps.restart();
    if(this->clock.getElapsedTime().asSeconds() >= 1)
    {
        this->fps = this->average;
        this->clock.restart();
    }
}

void FPS::restart()
{
    
    clock.restart();
    clockFps.restart();
    fps = 0;
    average = 0;
}
