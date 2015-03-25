//
//  Vector3D.cpp
//  profiler
//
//  Created by Yu Chen on 3/22/15.
//
//

#include "../include/Vector3D.h"


Vector3D::Vector3D(float x, float y, float z) : x(x), y(y), z(z) {
}

void Vector3D::operator=(const Vector3D& obj)
{
    this->setXYZ(obj.x, obj.y, obj.z);
}

float Vector3D::getX() {
    return this->x;
}
float Vector3D::getY() {
    return this->y;
}
float Vector3D::getZ() {
    return this->z;
}

void Vector3D::setX(float x) {
    this->x = x;
}

void Vector3D::setY(float y) {
    this->y = y;
}

void Vector3D::setZ(float z) {
    this->z = z;
}

void Vector3D::setXY(float x, float y) {
    this->setX(x);
    this->setY(y);
}

void Vector3D::setXYZ(float x, float y, float z) {
    this->setXY(x, y);
    this->setZ(z);
}

void Vector3D::setXYZ(const Vector3D& v) {
    this->setXYZ(v.x, v.y, v.z);
}

float Vector3D::magnitude() {
    return std::sqrtf(std::powf(this->getX(), 2)
                      + std::powf(this->getY(), 2)
                      + std::powf(this->getZ(), 2));
}

void Vector3D::normalize() {
    float m = magnitude();
    if (m > 0)
        div(m);
}

void Vector3D::limit(float max) {
    if (magnitude() > max) {
        normalize();
        mul(max);
    }
}

float Vector3D::distance (const Vector3D& v) {
    float dx = x - v.x;
    float dy = y - v.y;
    float dz = z - v.z;
    return std::sqrtf(dx*dx + dy*dy + dz*dz);
}

float Vector3D::heading2D() {
    return -std::atan2f(-this->getY(), this->getX());
}

void Vector3D::add(const Vector3D& v) {
    x += v.x;
    y += v.y;
    z += v.z;
}

void Vector3D::operator+=(const Vector3D& v) {
    add(v);
}

void Vector3D::sub(const Vector3D& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

void Vector3D::operator-=(const Vector3D& v) {
    sub(v);
}

void Vector3D::mul(float n) {
    x *= n;
    y *= n;
    z *= n;
}

void Vector3D::operator*=(float n) {
    mul(n);
}

void Vector3D::div(float n) {
    x /= n;
    y /= n;
    z /= n;
}

void Vector3D::operator/=(float n) {
    div(n);
}

Vector3D Vector3D::operator+(const Vector3D& v) const {
    return Vector3D(x + v.x, y + v.y, z + v.z);
}

Vector3D Vector3D::operator-(const Vector3D& v) const {
    return Vector3D(x - v.x, y - v.y, z - v.z);
}

Vector3D Vector3D::operator/(float n) const {
    return Vector3D(x/n, y/n, z/n);
}

Vector3D Vector3D::operator*(float n) const {
    return Vector3D(x*n, y*n, z*n);
}