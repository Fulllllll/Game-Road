#include"stdafx.h"
#include"Game.h"

int main()
{
	srand(static_cast<unsigned>(time(0)));
	while (1)
	{
		Game game;
		try
		{
			while (game.running())
			{
				game.update();
				game.render();

			}
			return 0;
		}
		catch (Player)
		{

		}
		catch (int)
		{

		}
	}

	return 0;
}