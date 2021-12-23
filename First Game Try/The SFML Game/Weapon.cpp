#include "stdafx.h"
#include "Weapon.h"

Weapon::Weapon()
{
	tex.loadFromFile("using gun.png");
	sprite.setTexture(tex);
	sprite.setOrigin(20,50);
}

Weapon::~Weapon()
{
}

void Weapon::setpos(Player player)
{
}

float Weapon::getrotation(sf::RenderWindow& window, bool _flag)
{
	{
		float ans = 180 * atan2(sf::Mouse::getPosition(window).y - 440, sf::Mouse::getPosition(window).x - 740) / 3.14;
		if (_flag == 0) {
			if (ans >= 90)
				return 90;
			else if (ans <= -90)
				return -90;
			else
				return ans;
		}
		else {
			if (ans > 0 && ans < 90)
				return -90;
			else if (ans < 0 && ans > -90)
				return 90;
			else if (ans > 0)
				return ans - 180;
			else
				return ans + 180;
		}
	}
}

void Weapon::update(Player player, sf::RenderWindow& window)
{
	weapon_pos.x = player.pos.x;
	weapon_pos.y = player.pos.y - 20;
	sprite.setPosition(weapon_pos);
	if (sf::Mouse::getPosition(window).x > 750)
	{
		sprite.setScale(1.f, 1.f);
		flag = 0;
	}
	else
	{
		sprite.setScale(-1.f, 1.f);
		flag = 1;
	}
	sprite.setRotation(getrotation(window, flag));
}


void Weapon::render(sf::RenderTarget& target)
{
	target.draw(sprite);
}
