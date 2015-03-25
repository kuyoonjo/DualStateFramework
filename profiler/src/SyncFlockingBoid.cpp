//
//  SyncFlockingBoid.cpp
//  profiler
//
//  Created by Yu Chen on 3/12/15.
//
//

#include "../include/SyncFlockingBoid.h"

SyncFlockingBoid::SyncFlockingBoid() : dsf::SynchronizedObject::SynchronizedObject(), sf::CircleShape::CircleShape()
{
}
SyncFlockingBoid::~SyncFlockingBoid()
{
    delete this->acc;
    delete this->vel;
    delete this->loc;
}
SyncFlockingBoid::SyncFlockingBoid(Vector3D* loc, float ms, float mf) : dsf::SynchronizedObject::SynchronizedObject(), sf::CircleShape::CircleShape()
{
    this->acc = new SyncVector3D(0,0);
    this->vel = new SyncVector3D(yc::Random().randFloat(-1,1), yc::Random().randFloat(-1,1));
    this->loc = new SyncVector3D(loc->getX(), loc->getY(), loc->getZ());
    delete loc;
    r = 2.0f;
    maxspeed = ms;
    maxforce = mf;
}

void SyncFlockingBoid::run(std::vector<SyncFlockingBoid*>* boids, sf::RenderWindow* window) {
    //flock(boids);
    //update();
    //borders(window->getSize().x, window->getSize().y);
    //render(window);
    
    // We accumulate a new acceleration each time based on three rules
    Vector3D sep = separate(boids);   // Separation
    Vector3D ali = align(boids);      // Alignment
    Vector3D coh = cohesion(boids);   // Cohesion
    
    // Arbitrarily weight these forces
    sep *= 2.0f;
    ali *= 1.0f;
    coh *= 1.0f;
    
    auto acc = Vector3D(*this->acc);
    auto loc = Vector3D(this->loc->getX(), this->loc->getY());
    auto vel = Vector3D(*this->vel);
    
    // Add the force vectors to acceleration
    acc += sep;
    acc += ali;
    acc += coh;
    
    // Method to update location
    // Update velocity
    vel += acc;
    
    // Limit speed
    vel.limit(maxspeed);
    
    loc += vel;
    
    // Reset accelertion to 0 each cycle
    acc.setXYZ(0,0,0);
    
    // Wraparound
    auto width = window->getSize().x;
    auto height = window->getSize().y;
    if (loc.getX() < -r)
        loc.setX(width+r);
    if (loc.getY() < -r)
        loc.setY(height+r);
    if (loc.getX() > width+r)
        loc.setX(-r);
    if (loc.getY() > height+r)
        loc.setY(-r);
    
    
    this->acc->setXYZ(acc);
    this->loc->setXYZ(loc);
    this->vel->setXYZ(vel);
    this->setPosition(this->loc->getX(), this->loc->getY());
    this->setRadius(r);
}


// A method that calculates a steering vector towards a target
// Takes a second argument, if true, it slows down as it approaches the target

Vector3D SyncFlockingBoid::steer(Vector3D* target, bool slowdown) {
    Vector3D steer;  // The steering vector
    Vector3D desired = *target - *this->loc;  // A vector pointing from the location to the target
    float d = desired.magnitude(); // Distance from the target is the magnitude of the vector
    
    // If the distance is greater than 0, calc steering (otherwise return zero vector)
    if (d > 0) {
        // Normalize desired
        desired.normalize();
        
        // Two options for desired vector magnitude (1 -- based on distance, 2 -- maxspeed)
        if ((slowdown) && (d < 100.0f))
            desired *= maxspeed * (d / 100.0f); // This damping is somewhat arbitrary
        else
            desired *= maxspeed;
        
        // Steering = Desired minus Velocity
        steer = desired - *this->vel;
        steer.limit(maxforce);  // Limit to maximum steering force
        
    } else {
        steer = Vector3D(0,0);
    }
    return steer;
}

// Separation
// Method checks for nearby boids and steers away
Vector3D SyncFlockingBoid::separate (std::vector<SyncFlockingBoid*>* boids) {
    float desiredseparation = 25.0f;
    Vector3D sum = Vector3D(0,0,0);
    int count = 0;
    
    // For every boid in the system, check if it's too close
    for (auto other: *boids) {
        float d = this->loc->distance(*other->loc);
        
        // If the distance is greater than 0 and less than an arbitrary amount (0 when you are yourself)
        if ((d > 0) && (d < desiredseparation)) {
            // Calculate vector pointing away from neighbor
            Vector3D diff = *this->loc - *other->loc;
            diff.normalize();
            diff /= d;        // Weight by distance
            sum += diff;
            count++;            // Keep track of how many
        }
    }
    
    // Average -- divide by how many
    if (count > 0)
        sum /= count;
    return sum;
}



// Alignment
// For every nearby boid in the system, calculate the average velocity
Vector3D SyncFlockingBoid::align (std::vector<SyncFlockingBoid*>* boids) {
    float neighbordist = 50.0f;
    Vector3D sum = Vector3D(0,0,0);
    int count = 0;
    for (auto & other : *boids) {
        float d = this->loc->distance(*other->loc);
        if ((d > 0) && (d < neighbordist)) {
            sum += *other->vel;
            count++;
        }
    }
    if (count > 0) {
        sum /= count;
        sum.limit(maxforce);
    }
    return sum;
}

// Cohesion
// For the average location (i.e. center) of all nearby boids, calculate steering vector towards that location
Vector3D SyncFlockingBoid::cohesion (std::vector<SyncFlockingBoid*>* boids) {
    float neighbordist = 50.0f;
    Vector3D sum = Vector3D(0,0,0);   // Start with empty vector to accumulate all locations
    int count = 0;
    for (auto & other: *boids) {
        float d = this->loc->distance(*other->loc);
        if ((d > 0) && (d < neighbordist)) {
            sum += *other->loc; // Add location
            count++;
        }
    }
    
    if (count > 0) {
        sum /= count;
        return steer(&sum,false);  // Steer towards the location
    }
    return sum;
}

void SyncFlockingBoid::run()
{
    if(this->receive())
    {
        this->loc->synchronise();
        this->acc->synchronise();
        this->vel->synchronise();
        this->process();
    }
}