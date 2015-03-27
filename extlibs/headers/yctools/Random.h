//
//  Random.h
//  yctools
//
//  Created by Yu Chen on 2/9/15.
//
//

#ifndef yctools_Random_h
#define yctools_Random_h

#include <stdlib.h>
#include <ctime>
#include <random>

namespace yc
{
    namespace Random
    {
        int randInt(int min, int max)
        {
            std::random_device rd;
            std::default_random_engine generator(rd());
            std::uniform_int_distribution<int> distribution(min, max);
            int dice_roll = distribution(generator);
            return dice_roll;
        }
    }
}

#endif
