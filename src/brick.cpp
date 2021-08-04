//amirh_z

#include"brick.hpp"

Brick::Brick()
{
    this->is_broken = false;
    this->brick.setSize(Vector2f(36.f, 36.f));
}

Brick::~Brick(){}

FloatRect Brick::brick_box_collider()
{
    return this->brick.getGlobalBounds();
}

void Brick::set_brick_color(int r, int g, int b)
{
    this->brick.setFillColor(Color(r, g, b, 255));
}

void Brick::set_brick_pos(float x, float y)
{
    this->brick.setPosition(Vector2f(x, y));
}

void Brick::got_hit()
{
    this->is_broken = true;
}

bool Brick::brick_status()
{
    return this->is_broken;
}