#include "Game.h"



//私有函数
void Game::initVarbles()
{
	this->window = nullptr;

	//Game logic
	this->EndGame = false;
	this->points = 0;
	this->health = 30;
	this->enemySpawnTimerMax = 20.f;
	this->enemySpawnTimer = enemySpawnTimerMax;
	this->maxEnemies = 10;
	this->mouseHeld = false;
}

void Game::initWindow()
{
	videoMode.height = 600;
	videoMode.width = 800;
	window = new sf::RenderWindow(videoMode, "First", sf::Style::Default);
	this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		std::cout << "ERROR::failed to load font!" << "\n";
	}
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(25);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("None");
}

void Game::initEnemies()
{
	this->enemy.setPosition(10.f,10.f);
	this->enemy.setSize(sf::Vector2f(50.f, 50.f));
	this->enemy.setFillColor(sf::Color::Cyan);
	this->enemy.setOutlineThickness(1.f);
}

//构造与析构
Game::Game()
{
	this->initVarbles();
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initEnemies();
}

Game::~Game()
{
	delete window;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->EndGame;
}

//Functions
void Game::spawnEnemy()
{
	/*
		敌人的颜色，位置，形状(已确定)
		随机生成位置
		随机颜色
		添加至enemy vetor.

		敌人落地会被移除，点击会移除敌人
	*/

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),0
		/*static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))*/
	);

	//Randomize the enemy
	int type = rand() % 5;
	switch (type)
	{
	case(0):
		this->enemy.setFillColor(sf::Color::Magenta);
		this->enemy.setSize(sf::Vector2f(15.f, 15.f));
		break;
	case(1):
		this->enemy.setFillColor(sf::Color::Blue);
		this->enemy.setSize(sf::Vector2f(25.f, 25.f));
		break;
	case(2):
		this->enemy.setFillColor(sf::Color::Cyan);
		this->enemy.setSize(sf::Vector2f(35.f, 35.f));
		break;
	case(3):
		this->enemy.setFillColor(sf::Color::Green);
		this->enemy.setSize(sf::Vector2f(50.f, 50.f));
		break;
	case(4):
		this->enemy.setFillColor(sf::Color::Yellow);
		this->enemy.setSize(sf::Vector2f(70.f, 70.f));
		break;
	default:
		this->enemy.setFillColor(sf::Color::White);
		break;
	}
	

	//spawn
	this->enemies.push_back(this->enemy);
}
void Game::pollEvents()
{
	//Event rolling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::updataMousePostions()
{
	/*
		retrun void 
		updata the mouse positions:
			- Moes
	*/
	this->mousePosWindows = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindows);
}

void Game::updataText()
{
	std::stringstream ss;
	ss << "Points:" << this->points << "\n"
		<< "Health:" << this->health << "\n";
	this->uiText.setString(ss.str());
}

void Game::updataEnemies()
{
	/*
		根据 game 里的敌人生成时间及敌人数量，来生成updata敌人
		Moves the enemies downwards
		Remove the enemies at the edge of the screen.//TODO
	*/
	//updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else this->enemySpawnTimer += 1.f; 
	}

	//moving and updata the enemy 
	for (int i = 0; i < this->enemies.size();i++)	
	{
		this->enemies[i].move(0.f, 2.f);
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->health -= 1;
			this->enemies.erase(this->enemies.begin() + i);
		}
	}
	//check if click upon    
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!this->mouseHeld)
		{
			bool deleted = false;
			this->mouseHeld = true;
			for (int i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					//gain poits
					if(this->enemies[i].getFillColor()==sf::Color::Magenta)
						this->points += 10;
					if (this->enemies[i].getFillColor() == sf::Color::Blue)
						this->points += 4;
					if (this->enemies[i].getFillColor() == sf::Color::Cyan)
						this->points += 3;
					if (this->enemies[i].getFillColor() == sf::Color::Green)
						this->points += 2;
					if (this->enemies[i].getFillColor() == sf::Color::Yellow)
						this->points += 1;
					//delete
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
				}
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
			//右键可以按住攻击
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
			bool deleted = false;
			for (int i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					//delete
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
					//gain poits
					this->points += 1.f;
				}
			}
	}
}



void Game::updata()
{
	this->pollEvents();
	if (!this->EndGame)
	{
		this->updataEnemies();
		this->updataText();
		this->updataMousePostions();
	}
	if (this->health <= 0)
		this->EndGame = true;


	////relative to screen
	////std::cout << "Mouse pos" 
	////	<< sf::Mouse::getPosition().x << " "
	////	<< sf::Mouse::getPosition().y << "\n";
	////relative to windows
	//std::cout << "Mouse pos " 
	//	<< sf::Mouse::getPosition(*this->window).x << " "
	//	<< sf::Mouse::getPosition(*this->window).y << "\n";
}
void Game::randerText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}
void Game::renderEnemies(sf::RenderTarget& target)
{
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}
void Game::render()
{
	this->window->clear();

	this->renderEnemies(*this->window);

	this->randerText(*this->window);
	this->window->display();
}
