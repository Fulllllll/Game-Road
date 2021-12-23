
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "Animator.hpp"

////不使用animator 制造动画,
//int main(int argc, char const* argv[])
//{
//    sf::RenderWindow window(sf::VideoMode(640, 480), "Crystal");
//
//    AssetManager manager;
//
//
//    sf::Vector2i spriteSize(32, 32);
//    sf::Sprite sprite(AssetManager::GetTexture("crystal.png"));
//    //设置第一帧，
//    sprite.setTextureRect(sf::IntRect(0, 0, spriteSize.x, spriteSize.y));
//
//    //一秒 8帧
//    int framesNum = 8;
//    float animationDuration = 1; // 1 秒
//
//    sf::Clock clock;
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::EventType::Closed)
//                window.close();
//            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//                std::cout << sf::Mouse::getPosition().x <<"  "<< sf::Mouse::getPosition().y << "\n";
//        }
//
//        sf::Time dt = clock.restart();
//
//        sf::Time elapsedTime; 
//        elapsedTime += dt;
//        float timeAsSeconds = elapsedTime.asSeconds();
//        int animFrame = static_cast<int>((timeAsSeconds / animationDuration) * framesNum) % framesNum;
//        sprite.setTextureRect(sf::IntRect(animFrame * spriteSize.x, 0, spriteSize.x, spriteSize.y));
//        window.clear();
//        window.draw(sprite);
//        window.display();
//    }
//    return 0;
//}

//使用animator 制造动画  
int main(int argc, char const* argv[])
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Crystal");

    AssetManager manager;


    sf::Vector2i spriteSize(72, 96);
    sf::Sprite sprite;
    //sprite.setPosition(0, 0);   //relative to window
    //sprite.setOrigin(16,16);

    Animator animator(sprite);

    auto& idleAnimation = animator.CreateAnimation("Idle",
        "left1.png",
        sf::seconds(0.35),true);

   idleAnimation.AddFrames(sf::Vector2i(0, 0), spriteSize, 3);


    //texture load
    //sf::Texture texture1;
    //texture1.loadFromFile("crystal.png");
    //sf::Sprite sp(texture1);

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed)
                window.close();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                std::cout << sf::Mouse::getPosition().x <<"  "<< sf::Mouse::getPosition().y << "\n";
        }
        sf::Time dt = clock.restart();

        animator.Update(dt);

        window.clear();
        window.draw(sprite);
        //window.draw(sp);
        window.display();
    }
    return 0;
}