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
    FPS(float refreshTime);
    ~FPS();
    float getFPS();
    void refresh();
    void restart();
private:
    float refreshTime;
    sf::Clock clock;
    sf::Clock clockFps;
    float fps;
    float average;
};

#endif
