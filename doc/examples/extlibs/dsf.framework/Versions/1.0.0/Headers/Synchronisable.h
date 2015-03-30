//
//  Synchronisable.h
//  dsf
//
//  Created by Yu Chen on 3/24/15.
//
//

#ifndef dsf_Synchronisable_h
#define dsf_Synchronisable_h

namespace dsf {
    /*! \brief Synchronising two states.
     * \details The template interface provides a copy of current object, and a synchronise method which synchronise two copies.
     * \section Example
     @code
     #include <dsf/Synchronisable.h>
     
     class Vector3D
     {
     public:
         float x, y, z;
         Vector3D(float x, float y, float z) : x(x), y(y), z(z){}
     }
     
     class SyncVector : public dsf::Synchronisable<Vector3D>, public Vector3D
     {
     public:
         SyncInt(float x, float y, float z) : Vector3D(x, y, z) {
             this->next = new Vector3D(x, y, z);
         }
         void synchronise() override {
             this->x = this->next->x;
             this->y = this->next->y;
             this->z = this->next->z;
         }
     }
     @endcode
     */
    template<class T> class Synchronisable
    {
    protected:
        /*! A copy of current object. */
        T* next;
    public:
        virtual ~Synchronisable() {
            delete this->next;
        }
        /*! Signs current value to next value. */
        virtual void synchronise() = 0;
    };
}

#endif
