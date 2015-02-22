//
//  BouncingCircleManager.cpp
//  profiler
//
//  Created by Yu Chen on 2/22/15.
//
//

#include "../include/BouncingCircleManager.h"


BouncingCircleManager::BouncingCircleManager(MyDSF* dsf)
{
    this->dsf = dsf;
    this->create = new dsf::TaskFunction([this](dsf::SynchronizedObject* to, dsf::SynchronizedObject* from, dsf::TaskArgument* args)
                                         {
                                             SyncBouncingCircle* syncObj;
                                             std::vector<SyncBouncingCircle*>* syncObjs;
                                             std::tie(syncObj, syncObjs) = args->to<std::tuple<SyncBouncingCircle*, std::vector<SyncBouncingCircle*>*>>();
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
                                             SyncBouncingCircle* syncObj;
                                             std::vector<SyncBouncingCircle*>* syncObjs;
                                             std::tie(syncObj, syncObjs) = args->to<std::tuple<SyncBouncingCircle*, std::vector<SyncBouncingCircle*>*>>();
                                             if(this->dsf->window->isOpen())
                                             {
                                                 auto size = this->dsf->window->getSize();
                                                 for(auto & sb : *syncObjs)
                                                 {
                                                     if(sb != syncObj)
                                                         syncObj->collide(sb);
                                                 }
                                                 syncObj->move(size.x, size.y);
                                                 this->dsf->send(to, from, this->update, new dsf::TaskArgument(std::make_tuple(syncObj, syncObjs)));
                                             }
                                             else
                                             {
                                                 this->dsf->send(to, from, this->destroy, new dsf::TaskArgument(syncObj));
                                             }
                                         });
    this->destroy = new dsf::TaskFunction([this](dsf::SynchronizedObject* to, dsf::SynchronizedObject* from, dsf::TaskArgument* args)
                                          {
                                              auto syncObj = args->to<SyncBouncingCircle*>();
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
BouncingCircleManager::~BouncingCircleManager()
{
    delete this->create;
    delete this->update;
    delete this->destroy;
}

std::vector<SyncBouncingCircle*>* BouncingCircleManager::createRandomCircles(int number, int radius, int boundX, int boundY) {
    int numberOfCircles = number;
    auto circles = new std::vector<SyncBouncingCircle*>();
    SyncBouncingCircle* circle;
    while(circles->size() < numberOfCircles) {
        std::vector<SyncBouncingCircle*>::iterator itr = circles->begin();
        circle = createRandomCircle(radius, boundX, boundY);
        while (itr != circles->end()) {
            if (circle->hasCollision(*itr)) {
                circle = createRandomCircle(radius, boundX, boundY);
                itr = circles->begin();
            } else {
                itr ++;
            }
        }
        circles->push_back(circle);
    }
    return circles;
}

SyncBouncingCircle*  BouncingCircleManager::createRandomCircle(int radius, int boundX, int boundY) {
    SyncBouncingCircle* circle = new SyncBouncingCircle();
    int direction = yc::Random().randInt(1, 360);
    int posx = yc::Random().randInt(0, boundX - radius * 2);
    int posy = yc::Random().randInt(0, boundY - radius * 2);
    float x = cosf(direction * M_PI / 180);
    float y = sinf(direction * M_PI / 180);
    circle->setRadius(radius);
    circle->setPosition(sf::Vector2<float>(posx, posy));
    circle->setVelocity(sf::Vector2<float>(x, y));
    return circle;
}