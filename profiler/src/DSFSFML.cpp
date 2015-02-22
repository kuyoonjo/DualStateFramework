//
//  DSFSFML.cpp
//  profiler
//
//  Created by Yu Chen on 2/17/15.
//
//

#include "../include/DSFSFML.h"

namespace dsf
{
    namespace sfml
    {
        RenderWindow::RenderWindow()
        {
            this->window = new sf::RenderWindow();
            this->drawables = new std::vector<sf::Drawable*>();
        }

        RenderWindow::~RenderWindow()
        {
            delete this->window;
            delete this->drawables;
        }
    }
}

