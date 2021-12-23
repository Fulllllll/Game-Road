#include"Player.h"


class Weapon
{
	sf::Texture tex;
	bool flag = 0;
public:
	sf::Vector2f weapon_pos;
	sf::Sprite sprite;

	Weapon();
	virtual ~Weapon();

	void setpos(Player player);
	float getrotation(sf::RenderWindow& window, bool _flag);
	void update(Player player, sf::RenderWindow& window);
	void render(sf::RenderTarget& target);
};
