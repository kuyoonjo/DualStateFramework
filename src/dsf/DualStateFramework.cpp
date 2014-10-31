//
//  TaskManager.cpp
//  dsf
//
//  Created by Yu Chen on 10/17/14.
//
//

#include <dsf/DualStateFramework.h>

namespace dsf
{
    DualStateFramework::DualStateFramework()
    {
        this->syncObjs = new std::vector<SynchronizedObject*>();
        this->initialize();
        Debug("A DSF Object has been created.");
    }
    
    DualStateFramework::~DualStateFramework()
    {
        while (!this->syncObjs->empty()) {
            SynchronizedObject* syncObj = this->syncObjs->back();
            this->syncObjs->pop_back();
            delete syncObj;
        }
        delete this->syncObjs;
        Debug("A DSF Object has been removed.");
    }
    
    
    void DualStateFramework::tidy()
    {
        
    }
    void DualStateFramework::start()
    {
        this->doOneFrame();
        this->syncObjs->erase(std::remove_if(this->syncObjs->begin(),
                                               this->syncObjs->end(),
                                               [](SynchronizedObject* sb)
                                                    {
                                                        if (sb->isEmpty()) {
                                                            delete sb;
                                                            return true;
                                                        }
                                                        return false;
                                                    }) ,
                                this->syncObjs->end());
        if (!this->syncObjs->empty()) {
            this->start();
        }
    }
    void DualStateFramework::doOneFrame()
    {
        this->run();
    }
    
    void DualStateFramework::add(dsf::SynchronizedObject *syncObj)
    {
        this->syncObjs->push_back(syncObj);
    }
    
    //////////////////////////////////////////////////////////////////
    // Protected
    //////////////////////////////////////////////////////////////////

    
    void DualStateFramework::run()
    {
        for (auto i = this->syncObjs->begin();
             i != this->syncObjs->end();
             ++i)
        {
            (*i)->start();
        }
    }
}