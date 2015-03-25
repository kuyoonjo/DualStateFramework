//
//  SyncVector3D.h
//  profiler
//
//  Created by Yu Chen on 3/22/15.
//
//

#ifndef profiler_SyncVector3D_h
#define profiler_SyncVector3D_h

#include "Vector3D.h"
#include <dsf/Synchronisable.h>

class SyncVector3D : public dsf::Synchronisable<Vector3D>, public Vector3D {
public:
    explicit SyncVector3D(float x=0, float y=0, float z=0);
    void setX(float x) override;
    void setY(float y) override;
    void setZ(float z) override;
    void add(const Vector3D& v) override;
    void sub(const Vector3D& v) override;
    void mul(float n) override;
    void div(float n) override;
    void synchronise() override;
};

#endif
