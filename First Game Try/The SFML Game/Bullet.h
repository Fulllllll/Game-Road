#pragma once
#include"stdafx.h"
#include "Entity.h"
class Bullet :
    public Entity
{
    bool flag = 0;
public:
    float dx, dy;
    int angle;

    Bullet(sf::Vector2f pos0,sf::Vector2f post);

    void update();
    void render(sf::RenderTarget& target);
	float getrotation(sf::Vector2f post, int _flag);
};

