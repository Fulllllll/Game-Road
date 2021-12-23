
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "Animator.hpp"
#include "TileMap.hpp"
int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(512, 256), "Tilemap");

    // define the level with an array of tile indices
    const int level[] =
    {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1,
    };

    // create the tilemap from the level definition
    TileMap map;
    if (!map.load("145.png", sf::Vector2u(32, 32), level, 16, 8))
        return -1;

    // run the main loop
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // draw the map
        window.clear();
        window.draw(map);
        window.display();
    }

    return 0;
}
//
//int main(int argc, char const* argv[])
//{
//    sf::RenderWindow window(sf::VideoMode(640, 480), "Crystal");
//
//    AssetManager manager;
//
//
//    sf::Vector2i spriteSize(32, 32);
//    sf::Sprite sprite;
//    //sprite.setPosition(0, 0);   //relative to window
//    //sprite.setOrigin(16,16);
//
//    Animator animator(sprite);
//
//    auto& idleAnimation = animator.CreateAnimation("Idle",
//        "crystal.png",
//        sf::seconds(1), true);
//
//    idleAnimation.AddFrames(sf::Vector2i(0, 0), spriteSize, 8);
//
//
//    //texture load
//    //sf::Texture texture1;
//    //texture1.loadFromFile("crystal.png");
//    //sf::Sprite sp(texture1);
//
//    sf::Clock clock;
//    while (window.isOpen()) {
//        sf::Event event;
//
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::EventType::Closed)
//                window.close();
//            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//                std::cout << sf::Mouse::getPosition().x << "  " << sf::Mouse::getPosition().y << "\n";
//        }
//        sf::Time dt = clock.restart();
//
//        animator.Update(dt);
//
//        window.clear();
//        window.draw(sprite);
//        //window.draw(sp);
//        window.display();
//    }
//    return 0;
//}