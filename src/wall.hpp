//amirh_z

#pragma once
#include<SFML/Graphics.hpp>

using namespace sf;

class Wall
{
    private:

    public:
        Wall();
        ~Wall();

        RectangleShape wall;
        
        void set_wall_pos(float x, float y);
};