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

void profile(int maxNumberOfThreads, int numberOfObjects, int durationPerIterator, int method);
void configure();

// Constances
const sf::Vector2f WINDOW_SIZE(800, 600);
const int CHAR_SIZE = 20;
const sf::Vector2f LEFT_CORNER(100, 100);
const sf::Vector2f RIGHT_CORNER(700, 100);
const sf::Vector2f INTENT(500, 25);
const sf::Vector2f SHADOW_SIZE(WINDOW_SIZE.x - LEFT_CORNER.x * 2, INTENT.y);
const int MAX_NUMBER_OF_THREADS = 64;
const int MIN_NUMBER_OF_THREADS = 2;
const int MAX_NUMBER_OF_OBJECTS = 2000;
const int MIN_NUMBER_OF_OBJECTS = 100;
const int MAX_DURATION = 360;
const int MIN_DURATION = 5;
const int NUMBER_OF_PROFILING_METHODS = 3;
const std::string profilingMethods[NUMBER_OF_PROFILING_METHODS] = {
    "Random", "Collision", "Flocking"
};
const int NUMBER_OF_SELECTIONS = 4;
// Default Configurations
int currentSelection = 1;
int maxNumberOfThreads = 4;
int numberOfObjects = 1000;
int durationPerIterator = 60;
int profilingMethodIndex = 0;

int main()
{
    configure();
    return 0;
}

void configure()
{
    bool ready = false;
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "DSF Profiler");
    sf::Font font;
    sf::Text maxNumberOfThreadsText;
    sf::Text numberOfObjectsText;
    sf::Text durationPerIteratorText;
    sf::Text profilingMethodText;
    sf::Text maxNumberOfThreadsValue;
    sf::Text numberOfObjectsValue;
    sf::Text durationPerIteratorValue;
    sf::Text profilingMethodValue;
    sf::Text help;
    font.loadFromFile(resourcePath() + "sansation.ttf");
    maxNumberOfThreadsText.setFont(font);
    numberOfObjectsText.setFont(font);
    durationPerIteratorText.setFont(font);
    profilingMethodText.setFont(font);
    maxNumberOfThreadsValue.setFont(font);
    numberOfObjectsValue.setFont(font);
    durationPerIteratorValue.setFont(font);
    profilingMethodValue.setFont(font);
    help.setFont(font);
    maxNumberOfThreadsText.setCharacterSize(CHAR_SIZE);
    numberOfObjectsText.setCharacterSize(CHAR_SIZE);
    durationPerIteratorText.setCharacterSize(CHAR_SIZE);
    profilingMethodText.setCharacterSize(CHAR_SIZE);
    maxNumberOfThreadsValue.setCharacterSize(CHAR_SIZE);
    numberOfObjectsValue.setCharacterSize(CHAR_SIZE);
    durationPerIteratorValue.setCharacterSize(CHAR_SIZE);
    profilingMethodValue.setCharacterSize(CHAR_SIZE);
    help.setCharacterSize(CHAR_SIZE);
    maxNumberOfThreadsText.setPosition(LEFT_CORNER);
    numberOfObjectsText.setPosition(LEFT_CORNER.x, LEFT_CORNER.y + INTENT.y);
    durationPerIteratorText.setPosition(LEFT_CORNER.x, LEFT_CORNER.y + INTENT.y * 2);
    profilingMethodText.setPosition(LEFT_CORNER.x, LEFT_CORNER.y + INTENT.y * 3);
    maxNumberOfThreadsValue.setPosition(LEFT_CORNER.x + INTENT.x, LEFT_CORNER.y);
    numberOfObjectsValue.setPosition(LEFT_CORNER.x + INTENT.x, LEFT_CORNER.y + INTENT.y);
    durationPerIteratorValue.setPosition(LEFT_CORNER.x + INTENT.x, LEFT_CORNER.y + INTENT.y * 2);
    profilingMethodValue.setPosition(LEFT_CORNER.x + INTENT.x, LEFT_CORNER.y + INTENT.y * 3);
    help.setPosition(LEFT_CORNER.x, LEFT_CORNER.y + INTENT.y * 5);
    maxNumberOfThreadsText.setString("Max Number of Threads");
    numberOfObjectsText.setString("Number of Objects");
    durationPerIteratorText.setString("Duration per Iterator");
    profilingMethodText.setString("Profiling Method");
    help.setString("Press KeyUp, KeyDown, KeyLeft, and KeyRight to edit settings. \nPress Enter to run the application.");
    
    sf::RectangleShape shadow;
    shadow.setFillColor(sf::Color::Blue);
    shadow.setSize(SHADOW_SIZE);
    shadow.setPosition(LEFT_CORNER.x, LEFT_CORNER.y + INTENT.y * (currentSelection - 1));
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
            // Keyboard Events
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                ready = true;
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                if(currentSelection > 1)
                {
                    currentSelection --;
                    auto spos = shadow.getPosition();
                    shadow.setPosition(spos.x, spos.y - INTENT.y);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                if(currentSelection < NUMBER_OF_SELECTIONS)
                {
                    currentSelection ++;
                    auto spos = shadow.getPosition();
                    shadow.setPosition(spos.x, spos.y + INTENT.y);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                switch (currentSelection) {
                    case 1:
                        if(maxNumberOfThreads == MIN_NUMBER_OF_THREADS)
                            maxNumberOfThreads = MAX_NUMBER_OF_THREADS;
                        else
                            maxNumberOfThreads --;
                        break;
                    case 2:
                        if(numberOfObjects == MIN_NUMBER_OF_OBJECTS)
                            numberOfObjects = MAX_NUMBER_OF_OBJECTS;
                        else
                            numberOfObjects -= MIN_NUMBER_OF_OBJECTS;
                        break;
                    case 3:
                        if(durationPerIterator == MIN_DURATION)
                            durationPerIterator = MAX_DURATION;
                        else
                            durationPerIterator -= MIN_DURATION;
                        break;
                    case 4:
                        if(profilingMethodIndex == 0)
                            profilingMethodIndex = NUMBER_OF_PROFILING_METHODS - 1;
                        else
                            profilingMethodIndex --;
                        break;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                switch (currentSelection) {
                    case 1:
                        if(maxNumberOfThreads == MAX_NUMBER_OF_THREADS)
                            maxNumberOfThreads = MIN_NUMBER_OF_THREADS;
                        else
                            maxNumberOfThreads ++;
                        break;
                    case 2:
                        if(numberOfObjects == MAX_NUMBER_OF_OBJECTS)
                            numberOfObjects = MIN_NUMBER_OF_OBJECTS;
                        else
                            numberOfObjects += MIN_NUMBER_OF_OBJECTS;
                        break;
                    case 3:
                        if(durationPerIterator == MAX_DURATION)
                            durationPerIterator = MIN_DURATION;
                        else
                            durationPerIterator += MIN_DURATION;
                        break;
                    case 4:
                        if(profilingMethodIndex == NUMBER_OF_PROFILING_METHODS - 1)
                            profilingMethodIndex = 0;
                        else
                            profilingMethodIndex ++;
                        break;
                }
            }
        }
        
        maxNumberOfThreadsValue.setString(std::to_string(maxNumberOfThreads));
        numberOfObjectsValue.setString(std::to_string(numberOfObjects));
        durationPerIteratorValue.setString(std::to_string(durationPerIterator));
        profilingMethodValue.setString(profilingMethods[profilingMethodIndex]);
        // Clear screen
        window.clear();
        // Draw Items
        window.draw(shadow);
        window.draw(maxNumberOfThreadsText);
        window.draw(numberOfObjectsText);
        window.draw(durationPerIteratorText);
        window.draw(profilingMethodText);
        window.draw(maxNumberOfThreadsValue);
        window.draw(numberOfObjectsValue);
        window.draw(durationPerIteratorValue);
        window.draw(profilingMethodValue);
        window.draw(help);
        // Update the window
        window.display();
    }
    if (ready)
        profile(maxNumberOfThreads, numberOfObjects, durationPerIterator, profilingMethodIndex + 1);
}

void profile(int maxNumberOfThreads, int numberOfObjects, int durationPerIterator, int method)
{
    if(method == 1)
    {
        auto dsf = new MyDSF();
        auto rcm = new RandomCircleManager(dsf);
        std::vector<SyncCircle*> circles(numberOfObjects);
        for(auto & circle : circles)
        {
            circle = new SyncCircle();
            circle->setRadius(2);
            circle->setFillColor(sf::Color::Cyan);
            dsf->add(circle);
            dsf->send(circle, dsf->sender, rcm->create, new dsf::TaskArgument(circle));
        }
        dsf->duration = durationPerIterator;
        dsf->maxNumberOfCores = maxNumberOfThreads;
        dsf->start();
        delete dsf;
        delete rcm;
    }
    else if(method == 2)
    {
        auto dsf = new MyDSF();
        auto bcm = new BouncingCircleManager(dsf);
        auto bouncingCircles = bcm->createRandomCircles(numberOfObjects, 2, 800, 600);
        for(auto & bouncingCircle : *bouncingCircles)
        {
            bouncingCircle->setFillColor(sf::Color::Cyan);
            dsf->add(bouncingCircle);
            dsf->send(bouncingCircle,
                      dsf->sender,
                      bcm->create,
                      new dsf::TaskArgument(std::make_tuple(bouncingCircle, bouncingCircles)));
        }
        dsf->duration = durationPerIterator;
        dsf->maxNumberOfCores = maxNumberOfThreads;
        dsf->start();
        delete dsf;
        delete bcm;
    }
    else if(method == 3)
    {
        auto dsf = new MyDSF();
        auto flockingBoids = new std::vector<SyncFlockingBoid*>();
        auto fbm = new FlockingBoidManager(dsf);
        for (int i = 0; i < numberOfObjects; i++)
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
        dsf->duration = durationPerIterator;
        dsf->maxNumberOfCores = maxNumberOfThreads;
        dsf->start();
        delete dsf;
        delete fbm;
    }
    configure();
}