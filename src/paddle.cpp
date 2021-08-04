//amirh_z

#include"paddle.hpp"

Paddle::Paddle()
{
    this->paddle_speed = 5.f;
    
    this->paddle_pos.x = 468.f;
    this->paddle_pos.y = 715.f;
    
    this->paddle.setSize(Vector2f(144, 16));
    this->paddle.setFillColor(Color(147, 76, 142, 255));
    this->paddle.setPosition(this->paddle_pos);
}

Paddle::~Paddle(){}

FloatRect Paddle::paddle_box_collider()
{
    return this->paddle.getGlobalBounds();
}

void Paddle::move_left()
{
    this->paddle_pos.x -= this->paddle_speed;
}

void Paddle::move_right()
{
    this->paddle_pos.x += this->paddle_speed;
}

void Paddle::paddle_restart()
{
    this->paddle_pos.x = 468.f;
    this->paddle_pos.y = 715.f;
}

void Paddle::update_paddle_pos()
{
    this->paddle.setPosition(this->paddle_pos);
}