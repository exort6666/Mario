#include "Character.hpp"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    coords Start_pos{ 100, 400 };
    Character Hero(Start_pos);

    sf::RenderWindow window(sf::VideoMode(1200, 600), "SFML works!");

    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        deltaTime = deltaTime / 5000;
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            Hero.move({ 2,0 }, deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            Hero.move({ -2,0 }, deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (Hero.OnGround) && (!Hero.fall))
            Hero.OnGround = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && (!Hero.strike) && (!Hero.fall) && (Hero.OnGround)) {
                Hero.attack();
        }
        Hero.update(deltaTime);
        window.clear();
        Hero.draw(window);
        window.display();
        }
    return 0;
}