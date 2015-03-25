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
protected:
    float x;
    float y;
    float z;
public:
    explicit Vector3D(float x=0, float y=0, float z=0);
    virtual void operator=(const Vector3D& obj);
    
    float getX();
    float getY();
    float getZ();
    
    virtual void setX(float x);
    virtual void setY(float y);
    virtual void setZ(float z);
    
    void setXY(float x, float y);
    void setXYZ(float x, float y, float z);
    void setXYZ(const Vector3D& v);
    
    float magnitude();
    void normalize();
    void limit(float max);
    virtual float heading2D();
    float distance (const Vector3D& v);
    
    virtual void add(const Vector3D& v);
    void operator+=(const Vector3D& v);
    virtual void sub(const Vector3D& v);
    void operator-=(const Vector3D& v);
    virtual void mul(float n);
    void operator*=(float n);
    virtual void div(float n);
    void operator/=(float n);
    
    
    Vector3D operator+(const Vector3D& v) const;
    Vector3D operator-(const Vector3D& v) const;
    Vector3D operator/(float n) const;
    Vector3D operator*(float n) const;
    
};

#endif
