//
//  FlockingBoidManager.cpp
//  profiler
//
//  Created by Yu Chen on 3/12/15.
//
//

#include "../include/FlockingBoidManager.h"


FlockingBoidManager::FlockingBoidManager(MyDSF* dsf)
{
    this->dsf = dsf;
    this->create = new dsf::TaskFunction([this](dsf::SynchronizedObject* to, dsf::SynchronizedObject* from, dsf::TaskArgument* args)
                                         {
                                             SyncFlockingBoid* syncObj;
                                             std::vector<SyncFlockingBoid*>* syncObjs;
                                             std::tie(syncObj, syncObjs) = args->to<std::tuple<SyncFlockingBoid*, std::vector<SyncFlockingBoid*>*>>();
                                             if(this->dsf->window->isOpen())
                                             {
                                                 this->dsf->send(to, from, this->update, new dsf::TaskArgument(std::make_tuple(syncObj, syncObjs)));
                                                 this->dsf->lock();
                                                 this->dsf->drawables->push_back(syncObj);
                                                 this->dsf->unlock();
                                             }
                                             else
                                             {
                                                 this->dsf->send(to, from, this->destroy, new dsf::TaskArgument(syncObj));
                                             }
                                         });
    this->update = new dsf::TaskFunction([this](dsf::SynchronizedObject* to, dsf::SynchronizedObject* from, dsf::TaskArgument* args)
                                         {
                                             SyncFlockingBoid* syncObj;
                                             std::vector<SyncFlockingBoid*>* syncObjs;
                                             std::tie(syncObj, syncObjs) = args->to<std::tuple<SyncFlockingBoid*, std::vector<SyncFlockingBoid*>*>>();
                                             if(this->dsf->window->isOpen())
                                             {
                                                 syncObj->run(syncObjs, this->dsf->window);
                                                 this->dsf->send(to, from, this->update, new dsf::TaskArgument(std::make_tuple(syncObj, syncObjs)));
                                             }
                                             else
                                             {
                                                 this->dsf->send(to, from, this->destroy, new dsf::TaskArgument(syncObj));
                                             }
                                         });
    this->destroy = new dsf::TaskFunction([this](dsf::SynchronizedObject* to, dsf::SynchronizedObject* from, dsf::TaskArgument* args)
                                          {
                                              auto syncObj = args->to<SyncFlockingBoid*>();
                                              auto drawable = (sf::Drawable*) syncObj;
                                              this->dsf->lock();
                                              this->dsf->drawables->erase(
                                                                          std::remove_if(
                                                                                         this->dsf->drawables->begin(),
                                                                                         this->dsf->drawables->end(),
                                                                                         [&](sf::Drawable* d)
                                                                                         {
                                                                                             return d == drawable;
                                                                                         }),
                                                                          this->dsf->drawables->end());
                                              this->dsf->remove(to);
                                              this->dsf->unlock();
                                          });
}
FlockingBoidManager::~FlockingBoidManager()
{
    delete this->create;
    delete this->update;
    delete this->destroy;
}
