#include "stdafx.h"
#include "Ball.h"


Fireball::Fireball(sf::Vector2f pos0, sf::Vector2f post)
{
	speed = 20;
	pos = pos0;
	health = 10;

	float p = (post.x - pos0.x);
	float q = (post.y - pos0.y - 40);
	dx = speed * p / sqrtf(p * p + q * q);
	dy = dx * q / p;

	p1.loadFromFile("ball.png");
	sprite11.setTexture(p1);

}


void Fireball::update()
{

	pos.x += dx;
	pos.y += dy;
	sprite11.setPosition(pos);

	if (pos.x > 9856.f || pos.x < 0 || pos.y>4576.f || pos.y < 0) health = 0;
}

void Fireball::render(sf::RenderWindow& target)
{
	target.draw(sprite11);
}
