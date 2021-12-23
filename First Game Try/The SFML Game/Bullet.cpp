#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(sf::Vector2f pos0, sf::Vector2f post)
{
	speed =3;
	pos = pos0;
	flag = post.x < pos0.x;
	angle = getrotation(post, flag);
	M_InitVariable(20, 10, "fire_blue.png");
	anim.set(p1, 0, 0, 32, 64, 16,0.1);
	anim.sprite.setPosition(pos.x,pos.y-26);
	if (flag == 0)
		anim.sprite.setRotation(angle + 90);
	else
		anim.sprite.setRotation(angle - 90);

	dx = cos(angle * 0.017453f) * speed*1.5;
	dy = sin(angle * 0.017453f) * speed*1.5;
}

void Bullet::update()
{
	anim.update();
	if (flag == 0)
		pos += {dx, dy};
	else
		pos += {-dx, -dy};

	anim.sprite.setPosition(pos.x,pos.y-26);
	if (pos.x > 9856.f || pos.x < 0 || pos.y>4576.f || pos.y < 0) health = 0;
}

void Bullet::render(sf::RenderTarget& target)
{
	target.draw(anim.sprite);
}

float Bullet::getrotation(sf::Vector2f post, int _flag) {
	float ans = 180 * atan2(post.y - 440, post.x - 750) / 3.14;
	if (_flag == 0) {
		if (ans > 0) {
			return ans;
		}
		else {
			return 360 + ans;
		}
	}
	else
		if (ans + 180 <= 360)
			return ans + 180;
		else
			return ans + 180 - 360;
		

	
}