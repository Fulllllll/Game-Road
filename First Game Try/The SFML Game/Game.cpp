#include"stdafx.h"
#include "Game.h"


Game::Game()
{
	this->InitWindow();
	this->InitView();
	InitVariable();
}
void Game::InitWindow()
{
	this->window.create(sf::VideoMode(1500, 900), "Game", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(60);

	t1.loadFromFile("test.png");
	s1.setTexture(t1);
	s1.setScale(3.6,3.6);
	s1.setOrigin(750/2, 450/2);

}
void Game::InitView()
{
	view.setCenter(3700.f, 2200.f);
	view.reset(sf::FloatRect(0, 0,2400, 1440)); 
	s1.setScale(3.6, 3.6);
	//view.reset(sf::FloatRect(0, 0, 4000, 2400));
	//s1.setScale(5.7, 5.7);
	//view.reset(sf::FloatRect(0, 0, 10000, 6000));
	window.setView(view);
}

void Game::InitVariable()
{
	BGM.openFromFile("Ouroboros.ogg");
	BGM.setLoop(true);
	BGM.play();

	font.loadFromFile("PixellettersFull.ttf");
	text.setFont(font);
	text.setCharacterSize(65);
	text.setFillColor(sf::Color::Red);

	player.setmap(cave);
	player.InitPos();
	for (int i = 0; i < 6; i++)
	{
		Enemy* p = new Enemy;
		p->setmap(cave);
		p->InitPos();
		enemies.push_back(p);
	}
	cave.update();
}

const bool Game::running() const
{
	return this->window.isOpen();
}


const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}

void Game::update()
{
	while (this->window.pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
			this->window.close();
		else if (this->event.type == sf::Event::KeyPressed && this->event.key.code == sf::Keyboard::Escape)
			this->window.close();
	}
	updategameevent();

	std::stringstream ss;
	ss << "Health:" << player.health << "\n"
		<< "Enemy:" << enemies.size();
	text.setString(ss.str());
	text.setPosition(player.anim.sprite.getPosition().x - 1150, player.anim.sprite.getPosition().y - 690);

	view.setCenter(player.anim.sprite.getPosition());
	s1.setPosition(player.anim.sprite.getPosition());
}

void Game::updategameevent()
{
	player.update(window);
	if (enemies.empty())
		throw(1);
	//µÐÈË×Óµ¯update
	for (auto i = enemies.begin(); i != enemies.end();)
	{
		Enemy* e = *i;

		for (auto j = e->balls.begin(); j != e->balls.end();j++)
		{
			Fireball* b = *j;
			if (pow(b->pos.x - player.pos.x, 2) + pow(b->pos.y - player.pos.y + 40, 2) <= 3600)
			{
				std::cout << "-1\n";
				player.health -= 10;

				player.hurt_clock.restart();

				b->health -= 10;
				if (player.health <= 0)
					throw(player);
			}
		}

		e->update(player.pos);
		
		if (e->health == 0)
		{
			i = enemies.erase(i);
			delete e;
		}
		else i++;
	}

	for (auto i = player.bullets.begin(); i != player.bullets.end(); i++)
	{
		Bullet* e = *i;
		
		for (auto j = enemies.begin(); j != enemies.end(); j++)
		{
			Enemy* b = *j;
			if (pow(b->pos.x - e->pos.x, 2) + pow(b->pos.y - e->pos.y, 2) <= 3600)
			{
				std::cout << "boom!\n";
				e->health -= 10;
				b->health -= 10;
				b->hurt_clock.restart();
			}
		}
	}

	gun.update(player, window);
}

void Game::render()
{
	this->window.clear();
	//Render game here
	window.setView(view);
	
	window.draw(s1);
	cave.render(this->window);

	player.render(window);
	gun.render(window);

	for (auto i = enemies.begin(); i != enemies.end();i++)
	{
		Enemy* e = *i;
		e->render(window);
	}


	window.draw(text);
	this->window.display();
}

//Game::~Game()
//{
//
//}
