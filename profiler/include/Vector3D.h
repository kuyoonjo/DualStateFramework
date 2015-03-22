//
//  Vector3D.h
//  profiler
//
//  Created by Yu Chen on 3/22/15.
//
//

#ifndef profiler_Vector3D_h
#define profiler_Vector3D_h

#include <cmath>

class Vector3D {
public:
    float x;
    float y;
    float z;
    
    Vector3D(float x_=0, float y_=0, float z_=0) {
        x = x_; y = y_; z = z_;
    }
    
    void setX(float x_) {
        x = x_;
    }
    
    void setY(float y_) {
        y = y_;
    }
    
    void setZ(float z_) {
        z = z_;
    }
    
    void setXY(float x_, float y_) {
        x = x_;
        y = y_;
    }
    
    void setXYZ(float x_, float y_, float z_) {
        x = x_;
        y = y_;
        z = z_;
    }
    
    void setXYZ(Vector3D v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    
    float magnitude() {
        return std::sqrtf(x*x + y*y + z*z);
    }
    
    Vector3D copy() {
        return Vector3D(x,y,z);
    }
    
    Vector3D copy(Vector3D v) {
        return Vector3D(v.x, v.y,v.z);
    }
    
    void add(Vector3D v) {
        x += v.x;
        y += v.y;
        z += v.z;
    }
    
    void sub(Vector3D v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }
    
    void mult(float n) {
        x *= n;
        y *= n;
        z *= n;
    }
    
    void div(float n) {
        x /= n;
        y /= n;
        z /= n;
    }
    
    void normalize() {
        float m = magnitude();
        if (m > 0)
            div(m);
    }
    
    void limit(float max) {
        if (magnitude() > max) {
            normalize();
            mult(max);
        }
    }
    
    float heading2D() {
        return -std::atan2f(-y, x);
    }
    
    Vector3D add(Vector3D v1, Vector3D v2) {
        return Vector3D(v1.x + v2.x,v1.y + v2.y, v1.z + v2.z);
    }
    
    Vector3D sub(Vector3D v1, Vector3D v2) {
        return Vector3D(v1.x - v2.x,v1.y - v2.y,v1.z - v2.z);
    }
    
    Vector3D div(Vector3D v1, float n) {
        return Vector3D(v1.x/n,v1.y/n,v1.z/n);
    }
    
    Vector3D mult(Vector3D v1, float n) {
        return Vector3D(v1.x*n,v1.y*n,v1.z*n);
    }
    
    float distance (Vector3D v1, Vector3D v2) {
        float dx = v1.x - v2.x;
        float dy = v1.y - v2.y;
        float dz = v1.z - v2.z;
        return std::sqrtf(dx*dx + dy*dy + dz*dz);
    }
};

#endif
