//
//  MyDSF.cpp
//  profiler
//
//  Created by Yu Chen on 2/8/15.
//
//

#include "../include/MyDSF.h"
#include "../include/MySyncObj.h"
#include "../include/FPS.h"
#include <dsf/TaskArgument.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <yctools/Random.h>

MyDSF::MyDSF()
: dsf::DualStateFramework::DualStateFramework()
{
    this->initialize();
}
MyDSF::~MyDSF()
{
    delete this->fps;
}

void MyDSF::initialize()
{
    this->sender = new Sender(this);
    this->fps = new FPS();
    this->add(this->sender);
    this->send(this->sender, this->sender, this->sender->create, new dsf::TaskArgument((dsf::sfml::RenderWindow*)this));
    this->window->create(sf::VideoMode(800, 600), "DSF Profiler");
}

void MyDSF::refresh()
{
    dsf::DualStateFramework::refresh();
}

void MyDSF::run()
{
    dsf::DualStateFramework::run();
    if (this->window->isOpen())
    {
        sf::Event event;
        while (this->window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                this->window->close();
            }
        }
        this->window->clear();
        this->draw();
        this->fps->refresh();
        std::cout << fps->current << std::endl;
        this->window->display();
    }
}

void MyDSF::draw()
{
    std::for_each(this->drawables->begin(), this->drawables->end(), [this](sf::Drawable* drawable)
                  {
                      this->window->draw(*drawable);
                  });
}

MyDSF::Sender::Sender(dsf::DualStateFramework* dsf)  : dsf::SynchronizedObject::SynchronizedObject()
{
    this->dsf = dsf;
    this->create = new dsf::TaskFunction([this](dsf::SynchronizedObject* to, dsf::SynchronizedObject* from, dsf::TaskArgument* args)
                                         {
                                             auto rw = args->to<dsf::sfml::RenderWindow*>();
                                             if(rw->window->isOpen())
                                             {
                                                 this->dsf->send(to, from, this->update, new dsf::TaskArgument(rw));
                                             }
                                             else
                                             {
                                                 this->dsf->send(to, from, this->destroy, nullptr);
                                             }
                                         });
    this->update = new dsf::TaskFunction([this](dsf::SynchronizedObject* to, dsf::SynchronizedObject* from, dsf::TaskArgument* args)
                                         {
                                             auto rw = args->to<dsf::sfml::RenderWindow*>();
                                             if(rw->window->isOpen())
                                             {
                                                 this->dsf->send(to, from, this->update, new dsf::TaskArgument(rw));
                                             }
                                             else
                                             {
                                                 this->dsf->send(to, from, this->destroy, nullptr);
                                             }
                                         });
    this->destroy = new dsf::TaskFunction([this](dsf::SynchronizedObject* to, dsf::SynchronizedObject* from, dsf::TaskArgument* args)
                                          {
                                              this->dsf->remove(to);
                                          });
}

MyDSF::Sender::~Sender()
{
    delete this->create;
    delete this->update;
    delete this->destroy;
}

void MyDSF::Sender::run()
{
    if(this->receive())
        this->process();
}

