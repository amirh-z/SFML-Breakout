//amirh_z

#include"ball.hpp"

Ball::Ball()
{
    this->ball_pos.x = 532.f;
    this->ball_pos.y = 699.f;
    this->ball.setPosition(ball_pos);

    this->ball.setFillColor(Color(147, 76, 142, 255));

    this->ball_vel.x = 0.f;
    this->ball_vel.y = 5.f;

    this->ball.setSize(Vector2f(16, 16));
}

Ball::~Ball(){}

FloatRect Ball::ball_box_collider()
{
    return this->ball.getGlobalBounds();
}

void Ball::rebound_x_axis()
{
    this->ball_vel.x = (-1) * (this->ball_vel.x);
}

void Ball::rebound_y_axis()
{
    this->ball_vel.y = (-1) * (this->ball_vel.y);
}

void Ball::rebound_brick(Brick& brick)
{

    if((this->ball_box_collider().top < brick.brick_box_collider().top) && (this->ball_box_collider().top + this->ball_box_collider().height > brick.brick_box_collider().top)
        && (this->ball_box_collider().left < brick.brick_box_collider().left) && (this->ball_box_collider().left + this->ball_box_collider().width > brick.brick_box_collider().left))
    {
        if((this->ball_vel.x > 0) && (this->ball_vel.y > 0))
        {
            this->rebound_x_axis();
            this->rebound_y_axis();
        }
        else if((this->ball_vel.x > 0) && (this->ball_vel.y < 0))
        {
            this->rebound_x_axis();
        }
        else
        {
            this->rebound_y_axis();
        }
    }
    else if((this->ball_box_collider().top < brick.brick_box_collider().top) && (this->ball_box_collider().top + this->ball_box_collider().height > brick.brick_box_collider().top)
            && (this->ball_box_collider().left < brick.brick_box_collider().left + brick.brick_box_collider().width) && (this->ball_box_collider().left + this->ball_box_collider().width > brick.brick_box_collider().left + brick.brick_box_collider().width))
    {
        if((this->ball_vel.x < 0) && (this->ball_vel.y > 0))
        {
            this->rebound_x_axis();
            this->rebound_y_axis();
        }
        else if((this->ball_vel.x < 0) && (this->ball_vel.y < 0))
        {
            this->rebound_x_axis();
        }
        else
        {
            this->rebound_y_axis();
        }
    }
    else if((this->ball_box_collider().top < brick.brick_box_collider().top + brick.brick_box_collider().height) && (this->ball_box_collider().top + this->ball_box_collider().height > brick.brick_box_collider().top + brick.brick_box_collider().height)
            && (this->ball_box_collider().left < brick.brick_box_collider().left) && (this->ball_box_collider().left + this->ball_box_collider().width > brick.brick_box_collider().left))
    {
        if((this->ball_vel.x > 0) && (this->ball_vel.y < 0))
        {
            this->rebound_x_axis();
            this->rebound_y_axis();
        }
        else if((this->ball_vel.x > 0) && (this->ball_vel.y > 0))
        {
            this->rebound_x_axis();
        }
        else
        {
            this->rebound_y_axis();
        }
    }
    else if((this->ball_box_collider().top < brick.brick_box_collider().top + brick.brick_box_collider().height) && (this->ball_box_collider().top + this->ball_box_collider().height > brick.brick_box_collider().top + brick.brick_box_collider().height)
            && (this->ball_box_collider().left < brick.brick_box_collider().left + brick.brick_box_collider().width) && (this->ball_box_collider().left + this->ball_box_collider().width > brick.brick_box_collider().left + brick.brick_box_collider().width))
    {
        if((this->ball_vel.x < 0) && (this->ball_vel.y < 0))
        {
            this->rebound_x_axis();
            this->rebound_y_axis();
        }
        if((this->ball_vel.x < 0) && (this->ball_vel.y > 0))
        {
            this->rebound_x_axis();
        }  
        else
        {
            this->rebound_y_axis();
        }
    }
    else
    {
        if((this->ball_box_collider().top < brick.brick_box_collider().top) && (this->ball_box_collider().top + this->ball_box_collider().height > brick.brick_box_collider().top))
        {
            this->rebound_y_axis();
        }
        if((this->ball_box_collider().top < brick.brick_box_collider().top + brick.brick_box_collider().height) && (this->ball_box_collider().top + this->ball_box_collider().height > brick.brick_box_collider().top + brick.brick_box_collider().height))
        {
            this->rebound_y_axis();
        }
        if((this->ball_box_collider().left < brick.brick_box_collider().left) && (this->ball_box_collider().left + this->ball_box_collider().width > brick.brick_box_collider().left))
        {  
            this->rebound_x_axis();
        }
        if((this->ball_box_collider().left < brick.brick_box_collider().left + brick.brick_box_collider().width) && (this->ball_box_collider().left + this->ball_box_collider().width > brick.brick_box_collider().left + brick.brick_box_collider().width))
        {
            this->rebound_x_axis();
        }
    } 

    brick.got_hit();
    brick.set_brick_color(50, 50, 50);
}

void Ball::rebound_paddle(Paddle paddle)
{
    float paddle_center_x = ((2.f * paddle.paddle_box_collider().left) + paddle.paddle_box_collider().width) / 2.f;
    float ball_center_x = ((2.f * this->ball_box_collider().left) + this->ball_box_collider().width) / 2.f;
    float offset = ball_center_x - paddle_center_x;

    if(offset == 0)
    {
        offset += 1.0;
    }
    
    this->ball_vel.x = offset / 10;
    this->rebound_y_axis();
}

void Ball::move_right_with_paddle(Paddle paddle)
{
    this->ball_pos.x += paddle.paddle_speed;
}

void Ball::move_left_with_paddle(Paddle paddle)
{
    this->ball_pos.x -= paddle.paddle_speed;
}

void Ball::ball_restart()
{
    this->ball_pos.x = 532.f;
    this->ball_pos.y = 699.f;

    this->ball_vel.x = 0.f;
    this->ball_vel.y = 5.f;
}

void Ball::update_ball_pos()
{
    if(this->is_moving_with_paddle == false){
        this->ball_pos.x += ball_vel.x;
        this->ball_pos.y += ball_vel.y;
    }

    this->ball.setPosition(ball_pos);
}