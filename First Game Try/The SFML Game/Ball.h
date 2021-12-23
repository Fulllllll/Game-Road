#pragma once
#include "Entity.h"
class Fireball :
    public Entity
{
    float dx, dy;
public:
    sf::Sprite sprite11;

    Fireball(sf::Vector2f pos0, sf::Vector2f post);


    void update();
    void render(sf::RenderWindow& target);

};

