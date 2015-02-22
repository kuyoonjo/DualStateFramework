#include <SFML/Graphics.hpp>
#include <dsf/DualStateFramework.h>
#include "../include/ResourcePath.hpp"
#include "../include/FPS.h"
#include "../include/MyDSF.h"
#include "../include/SyncCircle.h"
#include "../include/RandomCircleManager.h"
#include "../include/SyncBouncingCircle.h"
#include "../include/BouncingCircleManager.h"


int main()
{
    int method = 2;
    auto dsf = new MyDSF();
    auto rcm = new RandomCircleManager(dsf);
    auto bcm = new BouncingCircleManager(dsf);
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
    dsf->start();
    delete dsf;
    delete rcm;
    delete bcm;
    return 0;
}

/*
float* stretch(float arr[], float strelen[], int len, int maxLen);
const unsigned int NumberOfObjects = 1000;
const unsigned int MaxNumberOfThreads = 8;
const unsigned int NumberOfFrames = 200;
int main()
{
    MyDSF* dsf = nullptr;
    MySyncObj* objects[NumberOfObjects];
    sf::RenderWindow window(sf::VideoMode(600, 500), "DSF Profiler");
    sf::Font font;
    font.loadFromFile(resourcePath() + "sansation.ttf");
    FPS* fps = new FPS(1);
    int numberOfThreads = 1;
    int frameCount = 0;
    float fpsAt[MaxNumberOfThreads];
    float* barLength;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        if(numberOfThreads <= MaxNumberOfThreads)
        {
            sf::Text text("Number of Threads: " + std::to_string(numberOfThreads) + "\nFPS: " + std::to_string(fps->getFPS()), font);
            fps->refresh();
            window.draw(text);
            if(frameCount == NumberOfFrames)
            {
                std::cout << "Number of Threads: " << numberOfThreads << " FPS: " << fps->getFPS() << std::endl;
                fpsAt[numberOfThreads - 1] = fps->getFPS();
                frameCount = 0;
                numberOfThreads ++;
            }
            if(dsf == nullptr)
            {
                dsf = new MyDSF();
                for(int i = 0; i < NumberOfObjects; i ++)
                {
                    objects[i] = new MySyncObj();
                    dsf->add(objects[i]);
                    dsf->send(objects[i], objects[i], dsf->createObj, new dsf::TaskArgument(&window));
                }
                dsf->setNumberOfThreads(numberOfThreads);
                dsf->doOneFrame();
            }
            frameCount ++;
            for (int i = 0; i < NumberOfObjects; i ++)
            {
                window.draw(objects[i]->shape);
            }
            delete dsf;
            dsf = nullptr;
        }
        else
        {
            const float width = 500;
            const float height = 400;
            const sf::Vector2<float> origin(50, 450);
            const float thickness = 3;
            const float barThickness = 10;
            sf::RectangleShape x(sf::Vector2<float>(width, thickness));
            sf::RectangleShape y(sf::Vector2<float>(thickness, height));
            sf::RectangleShape fill(sf::Vector2<float>(thickness, thickness));
            x.setPosition(origin);
            y.setPosition(origin);
            fill.setPosition(origin - sf::Vector2<float>(thickness, 0));
            y.rotate(180);
            window.draw(x);
            window.draw(y);
            window.draw(fill);
            barLength = stretch(fpsAt, fpsAt, numberOfThreads, height);
            for(int i = 0; i < numberOfThreads; i ++)
            {
                sf::RectangleShape bar(sf::Vector2<float>(barThickness, barLength[i]));
                bar.setPosition(origin + sf::Vector2<float>(width / numberOfThreads * (i + 1), 0));
                bar.rotate(180);
                window.draw(bar);
            }
            
        }
        window.display();
    }
    delete fps;
    return 0;
}
*/
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