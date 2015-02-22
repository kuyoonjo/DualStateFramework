//
//  RandomCircleManager.cpp
//  profiler
//
//  Created by Yu Chen on 2/21/15.
//
//

#include "../include/RandomCircleManager.h"

RandomCircleManager::RandomCircleManager(MyDSF* dsf)
{
    this->dsf = dsf;
    this->create = new dsf::TaskFunction([this](dsf::SynchronizedObject* to, dsf::SynchronizedObject* from, dsf::TaskArgument* args)
                                         {
                                             auto syncObj = args->to<SyncCircle*>();
                                             if(this->dsf->window->isOpen())
                                             {
                                                 this->dsf->send(to, from, this->update, new dsf::TaskArgument(syncObj));
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
                                             auto syncObj = args->to<SyncCircle*>();
                                             if(this->dsf->window->isOpen())
                                             {
                                                 auto size = this->dsf->window->getSize();
                                                 auto radius = syncObj->getRadius();
                                                 syncObj->setPosition(
                                                                      yc::Random().randInt(0, size.x - 2 * radius),
                                                                      yc::Random().randInt(0, size.y - 2 * radius)
                                                                      );
                                                 this->dsf->send(to, from, this->update, new dsf::TaskArgument(syncObj));
                                             }
                                             else
                                             {
                                                 this->dsf->send(to, from, this->destroy, new dsf::TaskArgument(syncObj));
                                             }
                                         });
    this->destroy = new dsf::TaskFunction([this](dsf::SynchronizedObject* to, dsf::SynchronizedObject* from, dsf::TaskArgument* args)
                                          {
                                              auto syncObj = args->to<SyncCircle*>();
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
RandomCircleManager::~RandomCircleManager()
{
    delete this->create;
    delete this->update;
    delete this->destroy;
}