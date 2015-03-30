#ifndef DSFExample_ObjManager_h
#define DSFExample_ObjManager_h

#include "MyDSF.h"
#include "SyncObj.h"
#include <iostream>

class ObjManager
{
public:
    MyDSF* dsf;
    dsf::TaskFunction* print;
    
    ObjManager(MyDSF* dsf) : dsf(dsf) {  // Alias DSF pointer
        // Initialises TaskFunctions
        this->print = new dsf::TaskFunction([this](dsf::SynchronizedObject* to,
                                                   dsf::SynchronizedObject* from,
                                                   dsf::TaskArgument* args)
                                               {
                                                   auto syncObj = args->to<SyncObj*>();
                                                   std::cout << syncObj->getValue();
                                                   this->dsf->remove(to);
                                               });

    }
    ~ObjManager() {
        delete this->print;
    }
};

#endif
