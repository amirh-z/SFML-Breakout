//amirh_z

#pragma once
#include<SFML/Graphics.hpp>

using namespace sf;

class Brick
{
    public:
        Brick();
        ~Brick();

        bool is_broken;
        
        int value;

        RectangleShape brick;

        FloatRect brick_box_collider();

        void set_brick_color(int r, int g, int b);
        void set_brick_pos(float x, float y);
        void got_hit();
        bool brick_status();

};