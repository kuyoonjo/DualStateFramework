//
//  SynchronizedObject.cpp
//  dsf
//
//  Created by Yu Chen on 10/17/14.
//
//

#include <dsf/SynchronizedObject.h>

namespace dsf
{
    SynchronizedObject::SynchronizedObject()
    {
        this->taskBoxes = new std::vector<TaskBox*>();
        Debug("A SynchronizedObject Object has been created.");
    }
    SynchronizedObject::~SynchronizedObject()
    {
        std::for_each(this->taskBoxes->begin(),
                      this->taskBoxes->end(),
                      [](TaskBox* tb)
                      {
                          delete tb;
                      });
        delete this->taskBoxes;
        Debug("A SynchronizedObject Object has been removed.");
    }
    
    bool SynchronizedObject::isEmpty()
    {
        return this->taskBoxes->empty();
    }
    
    void SynchronizedObject::process(unsigned int index)
    {
        //this->taskBoxes->find(index)->second->start();
    }
    
    void SynchronizedObject::sendMessage(dsf::TaskBox *to,
                                dsf::TaskBox *from,
                                TaskFunction *taskFunction,
                                TaskArguments *args)
    {
        to->push(new Task(from, taskFunction, args));
    }
    
    void SynchronizedObject::add(dsf::TaskBox *taskBox)
    {
        this->taskBoxes->push_back(taskBox);
    }
    
    void SynchronizedObject::remove(std::string name)
    {
    }
    
    void SynchronizedObject::start()
    {
        this->run();
        this->taskBoxes->erase(std::remove_if(this->taskBoxes->begin(),
                                              this->taskBoxes->end(),
                                              [](TaskBox* tb)
                                              {
                                                  if (tb->isEmpty()) {
                                                      Debug("Removing a TaskBox");
                                                      delete tb;
                                                      return true;
                                                  }
                                                  return false;
                                              }),
                               this->taskBoxes->end());

        Debug("A SynchronizedObject has been finished.");
    }
    
    void SynchronizedObject::run()
    {
        for (auto i = this->taskBoxes->begin();
             i != this->taskBoxes->end();
             ++i)
        {
            Debug("Processing Tasks...");
            (*i)->start();
        }
        Debug("Ending a SynchronizedObject ...");
    }
}