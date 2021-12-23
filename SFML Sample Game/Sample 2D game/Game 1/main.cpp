#include<iostream>
#include "Game.h"
using namespace sf;

int main()
{
	std::srand(static_cast<unsigned>(time(NULL)));
	//Init Game engine
	Game game;
	//Game loop
	while (game.running()&&!game.getEndGame())
	{ 
		game.updata();
		game.render();
	}

	return 0;
}