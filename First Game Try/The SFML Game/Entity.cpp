#include "stdafx.h"
#include "Entity.h"

Entity::Entity()
{
	pos.x = 0;
	pos.y = 0;
	health = 0;
	speed = 0;
	speed_incline = 0;
}

void Entity::M_InitVariable(float _speed, float _health,const std::string& fliename)
{
	speed = _speed;
	health = _health;
	speed_incline = _speed / 1.414;

	p1.loadFromFile(fliename);

	dmove[0] = { -speed_incline,-speed_incline };
	dmove[1] = { 0,-speed };
	dmove[2] = { speed_incline,-speed_incline };
	dmove[3] = { -speed,0 };
	dmove[4] = { speed,0 };
	dmove[5] = { -speed_incline,speed_incline };
	dmove[6] = { 0,speed_incline };
	dmove[7] = { speed_incline,speed_incline };
}

void Entity::SetAnim(const std::string& fliename, int _x, int _y, int w, int h, int count, int fspeed)
{
	p1.loadFromFile(fliename);
	anim.set(p1, _x, _y, w, h, count, fspeed);
}

void Entity::update()
{
}

void Entity::render()
{
}

