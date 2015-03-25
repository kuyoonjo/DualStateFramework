//
//  Vector3D.cpp
//  profiler
//
//  Created by Yu Chen on 3/22/15.
//
//

#include "../include/SyncVector3D.h"


SyncVector3D::SyncVector3D(float x, float y, float z) : Vector3D(x, y, z) {
    this->next = new Vector3D(x, y, z);
}

void SyncVector3D::setX(float x) {
    this->next->setX(x);
}

void SyncVector3D::setY(float y) {
    this->next->setY(y);
}

void SyncVector3D::setZ(float z) {
    this->next->setZ(z);
}

void SyncVector3D::add(const Vector3D& v) {
    this->next->add(v);
}

void SyncVector3D::sub(const Vector3D& v) {
    this->next->sub(v);
}

void SyncVector3D::mul(float n) {
    this->next->mul(n);
}

void SyncVector3D::div(float n) {
    this->next->div(n);
}

void SyncVector3D::synchronise() {
    this->x = this->next->getX();
    this->y = this->next->getY();
    this->z = this->next->getZ();
}