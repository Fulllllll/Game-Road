#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	p = NULL;
	M_InitVariable(15, 100,"player1.png");

	anim.set(p1, 0, 0, 160, 160, 9, 0.2);
	anim.sprite.scale(0.8, 0.8);
	anim.sprite.setOrigin(80, 140);
	sf::Time firetime = sf::seconds(0);
	sf::Time hurttime = sf::seconds(5);
}


void  Player::update(sf::RenderWindow& target)
{

	updatemove(target);
	updatebullet(target);
	updatehurt();
}


void Player::updatemove(sf::RenderWindow& target)
{
	Mpos = sf::Mouse::getPosition(target);
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
	{
		anim.update();
	}
	else {
		anim.Frame = 8;
		anim.update();
	}
	//TODO	Ð±ÅÜÅöÇ½¼ÓÅÐ¶¨
	//		8 if ¼ò»¯s
	double scalenum=0.8;
	if(Mpos.x>750)
	{
		anim.sprite.setScale(scalenum, scalenum);
	}
	else 
	{
		anim.sprite.setScale(-scalenum, scalenum);
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)))
	{
		MOVE(dmove[0]);
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)))
	{
		MOVE(dmove[2]);
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)))
	{
		MOVE(dmove[5]);
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)))
	{
		MOVE(dmove[7]);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		MOVE(dmove[4]);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		MOVE(dmove[1]);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		MOVE(dmove[6]);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		MOVE(dmove[3]);
	}
}
void Player::updatebullet(sf::RenderWindow& target)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		firetime = clock.getElapsedTime();
		if (firetime >= sf::seconds(0.3)) {
			clock.restart();
			Bullet* p = new Bullet(pos, sf::Vector2f(sf::Mouse::getPosition(target)));
			p->anim.sprite.scale(1.5, 1.5);
			bullets.push_back(p);
		}
	}
	for (auto i = bullets.begin(); i != bullets.end();)
	{
		Bullet* e = *i;
		e->update();
		if (e->health == 0)
		{
			i = bullets.erase(i);
			delete e;
		}
		else i++;
	}
}
void Player::updatehurt()
{
	hurttime = hurt_clock.getElapsedTime();
	if (hurttime <= sf::seconds(0.125)) 
	{
		anim.sprite.setColor(sf::Color::Red);
	}
	else anim.sprite.setColor(sf::Color::White);
}
void Player::render(sf::RenderWindow& target)
{
	target.draw(anim.sprite);

	for (auto i = bullets.begin(); i != bullets.end();i++)
	{
		Bullet* e = *i;
		e->render(target);
	}
}


//Player::~Player()
//{
//}

void Player::setmap(Map& map)
{
	p = (int*)map.p;
}

void Player::InitPos()
{
	for (int i = 0; i < C; i++)
	{
		for (int j = 0; j < R; j++)
		{
			if (p[j * C + i] >= 4)
			{
				pos.x = i * 128 + 50;
				pos.y = j * 104 + 50;
				anim.sprite.setPosition(pos.x, pos.y);
				return;
			}
		}
	}
}

void Player::MOVE(sf::Vector2f dmove)
{
	if (p[int(pos.y + dmove.y) / 104 * C + int(pos.x + dmove.x) / 128] >= 4)
	{
		anim.sprite.move(dmove);
		pos += dmove;
	}
}