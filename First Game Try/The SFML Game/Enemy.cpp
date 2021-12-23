#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
	p = NULL;
	sf::Time firetime = sf::seconds(0.01 * (rand() % 20 + 1));
	sf::Time hurttime = sf::seconds(5);
	M_InitVariable(2, 50, "bird.png");

	anim.set(p1, 0, 0, 61, 57, 3, 0.1);
	anim.sprite.setScale(3, 3);
	anim.sprite.setOrigin(30.5, 55);

}

Enemy::~Enemy()
{
}

void Enemy::MOVE(sf::Vector2f dmove)
{
	if (p[int(pos.y + dmove.y) / 104 * C + int(pos.x + dmove.x) / 128] >=4)
	{
		anim.sprite.move(dmove);
		pos += dmove;
	}
}

void Enemy::update(sf::Vector2f playerpos)
{
	anim.update();
	dtime = clock.getElapsedTime();
	updatemove(playerpos);
	updatehurt();
	for (auto i = balls.begin(); i != balls.end();)
	{
		Fireball* e = *i;
		e->update();
		if (e->health == 0)
		{
			i = balls.erase(i);
			delete e;
		}
		else i++;
	}
	
}

void Enemy::updatemove(sf::Vector2f playerpos)
{
	if (statu == 0)
	{
		if (powf(playerpos.x - pos.x, 2) + powf(playerpos.y - pos.y, 2) <= 450000)
		{
			statu = 1;
		}
		if (dtime >= sf::seconds(2))
		{
			clock.restart();
			// TODO 移动算法改进
			//if(dmovenum==0||dmovenum==2||dmovenum==5||dmovenum==7)
			//{
			//	switch (dmovenum)
			//	{
			//	case 0:
			//		dmovenum = 4;
			//		break;
			//	case 2:
			//		dmovenum = 3;
			//		break;
			//	case 5:
			//		dmovenum = 0;
			//		break;
			//	case 7:
			//		dmovenum = 7;
			//		break;
			//	}
			//}
			/*else*/ dmovenum = rand() % 8;
		}
		MOVE(dmove[dmovenum]);
		if (dmovenum == 0 || dmovenum == 3 || dmovenum == 5 || dmovenum == 6)
		{
			anim.sprite.setScale(-3, 3);

		}
		else if (dmovenum == 1 || dmovenum == 2 || dmovenum == 4 || dmovenum == 7)
		{
			anim.sprite.setScale(3, 3);

		}
	}
	else if (statu == 1)
	{
		updatebullet(playerpos);
		if (dtime >= sf::seconds(1))
		{
			clock.restart();
			dmove1.x = ((playerpos.x - pos.x) > 0) - 0.4;
			dmove1.y = ((playerpos.y - pos.y) > 0) - 0.4;
			dmove1.x *= 1.4;
			dmove1.y *= 1.4;
			int rx = 0, ry = 0;
			while (1)
			{
				rx = rand() % 14 - 4;
				if (rx >= 3 || rx <= -3) break;
			}
			while (1)
			{
				ry = rand() % 14 - 4;
				if (ry >= 3 || ry <= -3) break;
			}
			dmove1.x *= rx;
			dmove1.y *= ry;
			//std::cout << dmove1.x<<"  "<<dmove1.y << "\n";
		}
		if (pos.x > playerpos.x)
			anim.sprite.setScale(-3, 3);
		else
			anim.sprite.setScale(3, 3);
		MOVE(dmove1);
	}
}

void Enemy::updatebullet(sf::Vector2f playerpos)
{
	firetime = clockfire.getElapsedTime();
	if (firetime >= sf::seconds(2)) {
		clockfire.restart();
		Fireball* p = new Fireball(pos, playerpos);
		p->anim.sprite.scale(1.5, 1.5);
		balls.push_back(p);
	}
}

void Enemy::render(sf::RenderWindow& target)
{
	target.draw(this->anim.sprite);
	for (auto i = balls.begin(); i != balls.end();)
	{
		Fireball* e = *i;
		e->render(target);
		if (e->health == 0)
		{
			i = balls.erase(i);
			delete e;
		}
		else i++;
	}
}

void Enemy::updatehurt()
{
	hurttime = hurt_clock.getElapsedTime();
	if (hurttime <= sf::seconds(0.125))
	{
		anim.sprite.setColor(sf::Color::Red);
	}
	else anim.sprite.setColor(sf::Color::White);
}

void Enemy::setmap(Map& map)
{
	p = (int*)map.p;
}

void Enemy::InitPos()
{
	int j;
	int i;
	while(1) 
	{
		j = rand() % (R - 2) + 1;
		i = rand() % (C - 2) + 1;
		if (p[j * C + i] >= 4)
		{
			pos.x = i * 128 + 50;
			pos.y = j * 104 + 50;
			anim.sprite.setPosition(pos.x, pos.y);
			return;
		}

	}
}
