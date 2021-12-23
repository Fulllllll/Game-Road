#pragma once
#include"stdafx.h"
#include"Map.h"
#include"BigCave_Generator.h"
#include"Player.h"
#include"Weapon.h"
#include"Enemy.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::View view;
	sf::Event event;
	sf::Music BGM;
	sf::Font font;
	sf::Text text;
	sf::Texture t1;
	sf::Sprite s1;
	BigCave_Generator cave; 
	Player player;
	Weapon gun;
	std::list <Enemy*> enemies;

	void InitWindow();
	void InitView();
	void InitVariable();
public:
	Game();

	const bool running() const;
	const sf::RenderWindow& getWindow() const;

	//update
	void update();
	void updategameevent();
	//render
	void render();

};

