#include "Character.hpp"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    coords Start_pos{100, 400};
    Character Hero(Start_pos);

    sf::RenderWindow window(sf::VideoMode(1200, 600), "SFML works!");

    sf::Clock clock;
    sf::Keyboard::Key lastKeyPressed;
    sf::Keyboard::Key previousKeyPressed;

    while (window.isOpen())
    {
        float deltaTime = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        deltaTime = deltaTime / 5000;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {
                previousKeyPressed = lastKeyPressed;
                lastKeyPressed = event.key.code;
        }
       // Hero.update(deltaTime);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            Hero.move({ 2,0 }, deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            Hero.move({-2,0 }, deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (Hero.OnGround) && (!Hero.fall))
            Hero.OnGround = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && (!Hero.strike) && (!Hero.fall) && (Hero.OnGround))
        {
            if (previousKeyPressed == sf::Keyboard::A)
                Hero.attack("left");
            if (previousKeyPressed == sf::Keyboard::D)
                Hero.attack("right");
        }

        Hero.update(deltaTime);
        window.clear();
        Hero.draw(window);
        window.display();
    }
    return 0;
}