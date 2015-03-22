//
//  SyncFlockingBoid.h
//  profiler
//
//  Created by Yu Chen on 3/12/15.
//
//

#ifndef profiler_SyncFlockingBoid_h
#define profiler_SyncFlockingBoid_h

#include <dsf/SynchronizedObject.h>
#include <SFML/Graphics.hpp>
#include <yctools/Random.h>
#include "Vector3D.h"

class SyncFlockingBoid : public dsf::SynchronizedObject, public sf::CircleShape
{
public:
    Vector3D loc;
    Vector3D vel;
    Vector3D acc;
    float r;
    float maxforce;    // Maximum steering force
    float maxspeed;    // Maximum speed
    SyncFlockingBoid();
    ~SyncFlockingBoid();
    SyncFlockingBoid(Vector3D l, float ms, float mf);
    void run(std::vector<SyncFlockingBoid*>* boids, sf::RenderWindow* window);
    void flock(std::vector<SyncFlockingBoid*>* boids);
    void update();
    void seek(Vector3D target);
    void arrive(Vector3D target);
    Vector3D steer(Vector3D target, bool slowdown);
    void render(sf::RenderWindow* window);
    void borders(int width, int height);
    Vector3D separate (std::vector<SyncFlockingBoid*>* boids);
    Vector3D align (std::vector<SyncFlockingBoid*>* boids);
    Vector3D cohesion (std::vector<SyncFlockingBoid*>* boids);
protected:
    void run() override;
};

#endif
