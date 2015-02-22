//
//  SyncBouncingCircle.cpp
//  profiler
//
//  Created by Yu Chen on 2/21/15.
//
//

#include "../include/SyncBouncingCircle.h"


SyncBouncingCircle::SyncBouncingCircle()  : dsf::SynchronizedObject::SynchronizedObject(), sf::CircleShape::CircleShape()
{
}

void SyncBouncingCircle::run()
{
    if(this->receive())
        this->process();
}

sf::Vector2<float> SyncBouncingCircle::getVelocity() {
    return this->velocity;
}
void SyncBouncingCircle::setVelocity(const sf::Vector2<float>& velocity) {
    this->velocity = velocity;
}
float SyncBouncingCircle::getMass() {
    return this->mass;
}
void SyncBouncingCircle::move(int width, int height) {
    sf::Vector2<float> nextPosition = this->getPosition() + this->velocity;
    this->setPosition(nextPosition);
    if (getPosition().x <= 0 || getPosition().x >= width - this->getRadius() * 2) {
        this->velocity = sf::Vector2<float>(-this->velocity.x, this->velocity.y);
    }
    if (getPosition().y <= 0 || getPosition().y >= height - this->getRadius() * 2) {
        this->velocity = sf::Vector2<float>(this->velocity.x, -this->velocity.y);
    }
}

void SyncBouncingCircle::collide(SyncBouncingCircle *sbc)
{
    if (this->hasCollision(sbc))
    {
        sf::Vector2<float> v1 = this->getVelocity();
        sf::Vector2<float> v2 = sbc->getVelocity();
        sf::Vector2<float> pos1 = this->getPosition();
        sf::Vector2<float> pos2 = sbc->getPosition();
        sf::Vector2<float> n = sf::Vector2<float>(pos2.x - pos1.x, pos2.y - pos1.y);
        sf::Vector2<float> un = n / sqrtf(n.x * n.x + n.y * n.y);
        sf::Vector2<float> ut = sf::Vector2<float>(-un.y, un.x);
        float v1n = un.x * v1.x + un.y * v1.y;
        float v1t = ut.x * v1.x + ut.y * v1.y;
        float v2n = un.x * v2.x + un.y * v2.y;
        float v2t = ut.x * v2.x + ut.y * v2.y;
        float m1 = this->getMass();
        float m2 = sbc->getMass();
        float v_1t = v1t;
        float v_2t = v2t;
        float v_1n = (v1n * (m1 - m2) + 2 * m2 * v2n) / (m1 + m2);
        float v_2n = (v2n * (m2 - m1) + 2 * m1 * v1n) / (m1 + m2);
        sf::Vector2<float> v__1n = v_1n * un;
        sf::Vector2<float> v__1t = v_1t * ut;
        sf::Vector2<float> v__2n = v_2n * un;
        sf::Vector2<float> v__2t = v_2t * ut;
        sf::Vector2<float> v_1 = v__1n + v__1t;
        sf::Vector2<float> v_2 = v__2n + v__2t;
        this->setVelocity(v_1);
        sbc->setVelocity(v_2);
    }
}

bool SyncBouncingCircle::hasCollision(SyncBouncingCircle *sbc)
{
    float distanceSqr = std::powf(this->getPosition().x - sbc->getPosition().x, 2) + std::powf(this->getPosition().y - sbc->getPosition().y, 2);
    return distanceSqr <= std::powf(this->getRadius() + sbc->getRadius(), 2);
}