//
//  FPS.cpp
//  profiler
//
//  Created by Yu Chen on 2/8/15.
//
//

#include "../include/FPS.h"

FPS::FPS(float refreshTime, float startTime)
{
    this->refreshTime = refreshTime;
    this->startTime = startTime;
}

FPS::~FPS()
{
    
}

void FPS::refresh()
{
    if(started)
    {
        if(!this->temp)
            this->temp = 1.0f / this->clockFps.getElapsedTime().asSeconds();
        else
            this->temp = (this->temp + 1.0f / this->clockFps.getElapsedTime().asSeconds()) / 2.0f;
        this->clockFps.restart();
        if(this->clock.getElapsedTime().asSeconds() >= refreshTime)
        {
            this->current = this->temp;
            this->temp = 0;
            if(this->average)
                this->average = (this->average + this->current) / 2.0f;
            else
                this->average = this->current;
            if(!this->max || this->max < this->current)
                this->max = this->current;
            if(!this->min || this->min > this->current)
                this->min = this->current;
            
            this->clock.restart();
        }
    }
    else if(this->clockStart.getElapsedTime().asSeconds() >= startTime)
    {
        this->started = true;
        this->clock.restart();
        this->clockFps.restart();
        this->current = this->average = this->max = this->min = this->temp = 0;
    }
}

void FPS::restart()
{
    this->clockStart.restart();
    this->started = false;
    this->current = this->average = this->max = this->min = this->temp = 0;
}
