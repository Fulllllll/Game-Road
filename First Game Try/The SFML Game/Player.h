#pragma once
#include "Entity.h"
#include "Map.h"
#include "Bullet.h"
#include"stdafx.h"
class Player :
    public Entity
{
private:
    sf::Vector2i Mpos;
    //bool bound(sf::Vector2f next_pos);
public:
    int* p = NULL;

    std::list <Bullet*> bullets;

    sf::Time firetime;
    sf::Clock hurt_clock;
    sf::Time hurttime;

    Player();
    void setmap(Map& map);
    void InitPos();
    void MOVE(sf::Vector2f dmove);

    void update(sf::RenderWindow& target);
    void updatemove(sf::RenderWindow& target);
    void updatebullet(sf::RenderWindow& target);
    void updatehurt();
    void render(sf::RenderWindow& target);
};
//class Player :
//    public Entity
//{
//public:
//    sf::Texture player1;
//    Animation player;
//    player1.
//
//    Player(float _x, float _y, float _speed, float _health) :
//        Entity(_x, _y, _speed, _health) {};
//
//    Animation player("π§≥Ã ¶.png", 0, 0, 160, 160, 8, 0.2);
//    void setanim();
//    void setrouge(float _r);
//};

