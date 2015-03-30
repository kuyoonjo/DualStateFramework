#ifndef DSFExample_SyncObj_h
#define DSFExample_SyncObj_h

#include <dsf/SynchronizedObject.h>

class SyncObj : public dsf::SynchronizedObject // Extends dsf::SynchronizedObject
{
public:
    SyncObj(int v) : SynchronizedObject(), v(v) {} // Uses default super constructor
    int getValue() {
        return this->v;
    }
protected:
    void run() override { // Overrides pure virtual function
        if(this->receive()) // Returns the number of message received
            this->process(); // Executes received messages
    }
private:
    int v;
};

#endif
