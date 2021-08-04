//amirh_z

#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<math.h>
#include<time.h>
#include"paddle.hpp"
#include"brick.hpp"

using namespace sf;
using namespace std;

class Ball
{
    public:
        Ball();
        ~Ball();

        bool is_moving_with_paddle;

        RectangleShape ball;

        FloatRect ball_box_collider();

        Vector2f ball_vel;
        Vector2f ball_pos;

        void rebound_x_axis();
        void rebound_y_axis();
        void rebound_brick(Brick& brick);
        void rebound_paddle(Paddle paddle);
        void move_right_with_paddle(Paddle paddle);
        void move_left_with_paddle(Paddle paddle);
        void ball_restart();
        void update_ball_pos();
};