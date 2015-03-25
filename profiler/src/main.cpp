#include <SFML/Graphics.hpp>
#include <dsf/DualStateFramework.h>
#include "../include/ResourcePath.hpp"
#include "../include/FPS.h"
#include "../include/MyDSF.h"
#include "../include/SyncCircle.h"
#include "../include/RandomCircleManager.h"
#include "../include/SyncBouncingCircle.h"
#include "../include/BouncingCircleManager.h"
#include "../include/SyncFlockingBoid.h"
#include "../include/FlockingBoidManager.h"


int main()
{
    int method = 3;
    auto dsf = new MyDSF();
    auto rcm = new RandomCircleManager(dsf);
    auto bcm = new BouncingCircleManager(dsf);
    auto fbm = new FlockingBoidManager(dsf);
    if(method == 1)
    {
        SyncCircle* circles[1000];
        for(auto & circle : circles)
        {
            circle = new SyncCircle();
            circle->setRadius(2);
            circle->setFillColor(sf::Color::Cyan);
            dsf->add(circle);
            dsf->send(circle, dsf->sender, rcm->create, new dsf::TaskArgument(circle));
        }
    }
    else if(method == 2)
    {
        auto bouncingCircles = bcm->createRandomCircles(1000, 2, 800, 600);
        for(auto & bouncingCircle : *bouncingCircles)
        {
            bouncingCircle->setFillColor(sf::Color::Cyan);
            dsf->add(bouncingCircle);
            dsf->send(bouncingCircle,
                      dsf->sender,
                      bcm->create,
                      new dsf::TaskArgument(std::make_tuple(bouncingCircle, bouncingCircles)));
        }
    }
    else if(method == 3)
    {
        auto flockingBoids = new std::vector<SyncFlockingBoid*>();
        for (int i = 0; i < 500; i++)
            flockingBoids->push_back(new SyncFlockingBoid(new Vector3D(dsf->window->getSize().x/2,dsf->window->getSize().y/2),2.0f,0.05f));
        for(auto & flockingBoid : *flockingBoids)
        {
            flockingBoid->setFillColor(sf::Color::Cyan);
            dsf->add(flockingBoid);
            dsf->send(flockingBoid,
                      dsf->sender,
                      fbm->create,
                      new dsf::TaskArgument(std::make_tuple(flockingBoid, flockingBoids)));
        }
    }
    dsf->start();
    delete dsf;
    delete rcm;
    delete bcm;
    return 0;
}

float* stretch(float arr[], float strelen[], int len, int maxLen)
{
    bool canDouble = true;
    for(int i = 0; i < len; i ++)
    {
        if(arr[i] + strelen[i] > maxLen)
        {
            canDouble = false;
            break;
        }
    }
    if(canDouble)
    {
        for(int i = 0; i < len; i ++)
        {
            arr[i] += strelen[i];
        }
        return stretch(arr, strelen, len, maxLen);
    }
    return arr;
}