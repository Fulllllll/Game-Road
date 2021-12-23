#pragma once
#include"stdafx.h"
#include"Animation.h"

class Entity
{
private:

public:
	//std::list <Entity*> ball;

	sf::Vector2f pos;
	int health;
	float speed, speed_incline;
	sf::Clock clock;
	sf::Vector2f dmove[8];

	Animation anim;
	sf::Texture p1;

	Entity();

	void M_InitVariable(float _speed,float _health, const std::string& fliename);
	void SetAnim(const std::string& fliename, int x,int y,int w,int h,int count,int fspeed);
	//void SetAnim(sf::Texture& ppp, int _x, int _y, int w, int h, int count, int fspeed);
	void update();
	void render();
};

