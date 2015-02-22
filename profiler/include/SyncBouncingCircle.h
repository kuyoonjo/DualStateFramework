//
//  SyncBouncingCircle.h
//  profiler
//
//  Created by Yu Chen on 2/21/15.
//
//

#ifndef profiler_SyncBouncingCircle_h
#define profiler_SyncBouncingCircle_h

#include <dsf/SynchronizedObject.h>
#include <SFML/Graphics.hpp>
#include <cmath>

class SyncBouncingCircle : public dsf::SynchronizedObject, public sf::CircleShape
{
public:
    SyncBouncingCircle();
    sf::Vector2<float> getVelocity();
    void setVelocity(const sf::Vector2<float>& velocity);
    float getMass();
    void move(int width, int height);
    void collide(SyncBouncingCircle* sbc);
    bool hasCollision(SyncBouncingCircle* sbc);
protected:
    void run() override;
private:
    sf::Vector2<float> velocity;
    float mass = 1;
};

#endif
