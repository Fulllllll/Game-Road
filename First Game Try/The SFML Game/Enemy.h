#pragma once
#include "Entity.h"
#include"Map.h"
#include"Bullet.h"
#include"Ball.h"
#include"stdafx.h"

class Enemy :
    public Entity
{
public:

    sf::Vector2f dmove1 = { 0,0 };

    int* p;
    sf::Time dtime=sf::seconds(0);
    int dmovenum = 0;
    int statu = 0;
    
    std::list <Fireball*> balls;

    sf::Clock clockfire;
    sf::Time firetime;
    sf::Clock hurt_clock;
    sf::Time hurttime = sf::seconds(5);

    Enemy();
    virtual ~Enemy();
    void MOVE(sf::Vector2f dmove);
    void setmap(Map& map);
    void InitPos();

    void update(sf::Vector2f playerpos);
    void updatemove(sf::Vector2f playerpos);
    void updatebullet(sf::Vector2f playerpos);
    void updatehurt();
    void render(sf::RenderWindow& target);
};

