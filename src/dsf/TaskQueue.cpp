//
//  TaskQueue.cpp
//  dsf
//
//  Created by Yu Chen on 10/17/14.
//
//

#include <dsf/TaskQueue.h>

namespace dsf
{
    TaskQueue::TaskQueue()
    {
        this->taskBoxes = new std::vector<TaskBox*>();
        Debug("A TaskQueue Object has been created.");
    }
    TaskQueue::~TaskQueue()
    {
        std::for_each(this->taskBoxes->begin(),
                      this->taskBoxes->end(),
                      [](TaskBox* tb)
                      {
                          delete tb;
                      });
        delete this->taskBoxes;
        Debug("A TaskQueue Object has been removed.");
    }
    
    bool TaskQueue::isEmpty()
    {
        return this->taskBoxes->empty();
    }
    
    void TaskQueue::process(unsigned int index)
    {
        //this->taskBoxes->find(index)->second->start();
    }
    
    void TaskQueue::sendMessage(dsf::TaskBox *to,
                                dsf::TaskBox *from,
                                TaskFunction *taskFunction,
                                TaskArguments *args)
    {
        to->push(new Task(from, taskFunction, args));
    }
    
    void TaskQueue::add(dsf::TaskBox *taskBox)
    {
        this->taskBoxes->push_back(taskBox);
    }
    
    void TaskQueue::remove(std::string name)
    {
    }
    
    void TaskQueue::start()
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

        Debug("A TaskQueue has been finished.");
    }
    
    void TaskQueue::run()
    {
        for (auto i = this->taskBoxes->begin();
             i != this->taskBoxes->end();
             ++i)
        {
            Debug("Processing Tasks...");
            (*i)->start();
        }
        Debug("Ending a TaskQueue ...");
    }
}