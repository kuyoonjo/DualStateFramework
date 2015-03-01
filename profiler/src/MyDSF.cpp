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
    delete this->clock;
}

void MyDSF::initialize()
{
    this->sender = new Sender(this);
    this->fps = new FPS();
    this->clock = new sf::Clock();
    this->add(this->sender);
    this->send(this->sender, this->sender, this->sender->create, new dsf::TaskArgument((dsf::sfml::RenderWindow*)this));
    this->window->create(sf::VideoMode(800, 600), "DSF Profiler");
    this->setNumberOfThreads(numberOfCores);
    this->font.loadFromFile(resourcePath() + "sansation.ttf");
}

void MyDSF::refresh()
{
    dsf::DualStateFramework::refresh();
}

void MyDSF::run()
{
    if(this->numberOfCores <= this->maxNumberOfCores
       && this->clock->getElapsedTime().asSeconds() >= this->duration)
    {
        this->fpsList.push_back(std::make_tuple(this->fps->average,
                                                this->fps->min,
                                                this->fps->max));
        this->clock->restart();
        this->fps->restart();
        this->numberOfCores ++;
        this->setNumberOfThreads(this->numberOfCores);
    }
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
        if(this->numberOfCores <= this->maxNumberOfCores)
        {
            if(this->fps->current)
            {
                std::string msg = "Number of Core: " + std::to_string(this->numberOfCores) + "\n";
                msg += "FPS \n";
                msg += " Current: " + std::to_string(fps->current) + "\n";
                msg += " Average: " + std::to_string(fps->average) + "\n";
                msg += " Min: " + std::to_string(fps->min) + "\n";
                msg += " Max: " + std::to_string(fps->max);
                sf::Text text(msg, font);
                this->window->draw(text);
            }
        }
        else
        {
            const float width = 700;
            const float height = 500;
            const sf::Vector2<float> origin(50, 550);
            const float thickness = 3;
            const float barThickness = 10;
            sf::RectangleShape x(sf::Vector2<float>(width, thickness));
            sf::RectangleShape y(sf::Vector2<float>(thickness, height));
            sf::RectangleShape fill(sf::Vector2<float>(thickness, thickness));
            x.setPosition(origin);
            y.setPosition(origin);
            fill.setPosition(origin - sf::Vector2<float>(thickness, 0));
            y.rotate(180);
            this->window->draw(x);
            this->window->draw(y);
            this->window->draw(fill);
            auto bars = stretch(this->fpsList, this->fpsList, height);
            for(int i = 0; i < this->fpsList.size(); i ++)
            {
                unsigned int charSize = 12;
                float x = width / (this->fpsList.size() + 1) * (i + 1);
                float average;
                float min;
                float max;
                float averageBar;
                float minBar;
                float maxBar;
                std::tie(averageBar, minBar, maxBar) = bars[i];
                std::tie(average, min, max) = this->fpsList[i];
                sf::RectangleShape bar(sf::Vector2<float>(barThickness, maxBar - minBar));
                bar.setPosition(origin + sf::Vector2<float>(x, -minBar));
                bar.rotate(180);
                sf::Text textAverage(std::to_string(average), this->font);
                textAverage.setCharacterSize(charSize);
                textAverage.setPosition(origin + sf::Vector2<float>(x, -averageBar));
                sf::Text textMin(std::to_string(min), this->font);
                textMin.setCharacterSize(charSize);
                textMin.setPosition(origin + sf::Vector2<float>(x, -minBar));
                sf::Text textMax(std::to_string(max), this->font);
                textMax.setCharacterSize(charSize);
                textMax.setPosition(origin + sf::Vector2<float>(x, -maxBar));
                sf::Text textCore(std::to_string(i + 1), this->font);
                textCore.setCharacterSize(14);
                textCore.setPosition(origin + sf::Vector2<float>(x, 0));
                this->window->draw(bar);
                this->window->draw(textAverage);
                this->window->draw(textMin);
                this->window->draw(textMax);
                this->window->draw(textCore);
            }
        }
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

std::vector<std::tuple<float,float,float>> MyDSF::stretch(std::vector<std::tuple<float,float,float>> arr,
                                                   std::vector<std::tuple<float,float,float>> strelen,
                                                   int maxLen)
{
    bool canDouble = true;
    for(int i = 0; i < arr.size(); i ++)
    {
        float average;
        float min;
        float max;
        float averageOrigin;
        float minOrigin;
        float maxOrigin;
        std::tie(average, min, max) = arr[i];
        std::tie(averageOrigin, minOrigin, maxOrigin) = strelen[i];
        if(max + maxOrigin > maxLen)
        {
            canDouble = false;
            break;
        }
    }
    if(canDouble)
    {
        for(int i = 0; i < arr.size(); i ++)
        {
            float average;
            float min;
            float max;
            float averageOrigin;
            float minOrigin;
            float maxOrigin;
            std::tie(average, min, max) = arr[i];
            std::tie(averageOrigin, minOrigin, maxOrigin) = strelen[i];
            arr[i] = std::make_tuple(average + averageOrigin,
                                     min + minOrigin,
                                     max + maxOrigin);
        }
        return stretch(arr, strelen, maxLen);
    }
    return arr;
}
