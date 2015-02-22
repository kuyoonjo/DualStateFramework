//
//  FPS.h
//  profiler
//
//  Created by Yu Chen on 2/8/15.
//
//

#ifndef profiler_FPS_h
#define profiler_FPS_h

#include <SFML/Graphics.hpp>

class FPS
{
public:
    FPS(float refreshTime = 1.0, float startTime = 1.0);
    ~FPS();
    void refresh();
    void restart();
    float current;
    float average;
    float max;
    float min;
private:
    bool started;
    float refreshTime;
    float startTime;
    sf::Clock clock;
    sf::Clock clockFps;
    sf::Clock clockStart;
    float temp;
};

#endif
