#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
class Game
{
private: 
	//Veriables
	//windows
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Mouse positions
	sf::Vector2i mousePosWindows;
	sf::Vector2f mousePosView;

	//Resources
	sf::Font font;

	//Text
	sf::Text uiText;

	//Game logic
	bool EndGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	//Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	//Priavte functions
	void initVarbles();
	void initWindow();
	void initFonts();
	void initText();
	void initEnemies();
public:
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;
	const bool getEndGame() const;

	//Functions
	void spawnEnemy();
	void pollEvents();
	void updataMousePostions();
	void updataText();
	void updataEnemies();
	void updata();

	void randerText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();
};

  