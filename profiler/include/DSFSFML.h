//
//  DSFSFML.h
//  profiler
//
//  Created by Yu Chen on 2/16/15.
//
//

#ifndef profiler_DSFSFML_h
#define profiler_DSFSFML_h

#include <SFML/Graphics.hpp>
#include <vector>

namespace dsf
{
    namespace sfml
    {
        class RenderWindow
        {
        public:
            explicit RenderWindow();
            virtual ~RenderWindow();
            sf::RenderWindow* window;
            std::vector<sf::Drawable*>* drawables;
        protected:
            virtual void draw() = 0;
        };
    }
}
#endif
