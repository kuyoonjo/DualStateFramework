//
//  Random.cpp
//  yctools
//
//  Created by Yu Chen on 2/9/15.
//
//


#include <yctools/Random.h>

int yc::Random::randInt(int min, int max)
{
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    int dice_roll = distribution(generator);
    return dice_roll;
}

float yc::Random::randFloat(float min, float max)
{
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<float> distribution(min, max);
    float dice_roll = distribution(generator);
    return dice_roll;
}