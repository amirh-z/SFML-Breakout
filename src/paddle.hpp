//amirh_z

#pragma once
#include<SFML/Graphics.hpp>

using namespace sf;

class Paddle
{
    public:
        Paddle();
        ~Paddle();

        float paddle_speed;

        RectangleShape paddle;
        FloatRect paddle_box_collider();
        Vector2f paddle_pos;

        void move_left();
        void move_right();
        void paddle_restart();
        void update_paddle_pos();
};