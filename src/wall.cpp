//amirh_z

#include"wall.hpp"

Wall::Wall()
{
    this->wall.setSize(Vector2f(36.f, 36.f));
    this->wall.setFillColor(Color(168, 170,167, 255));
}

Wall::~Wall(){}

void Wall::set_wall_pos(float x, float y)
{
    this->wall.setPosition(Vector2f(x, y));
}