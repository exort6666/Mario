#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>

struct coords {
    float x;
    float y;
};

int ground = 100;

class Character {
private:
    sf::Texture Pers;
    sf::Sprite Sprite;
    coords Pos;
    double currentFrame = 0;
    float jumpHeight = 100;

public:
    bool OnGround;

    Character(coords _pos) {
        Pos = _pos;
        OnGround = true;
        Pers.loadFromFile("AnimatedPers/Comparison2x.png");
        Sprite.setTexture(Pers);
        Sprite.setPosition(Pos.x, Pos.y);
        relax();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(Sprite);
    }

    void relax(){
        Sprite.setTextureRect(sf::IntRect(50, 30, 100, 80));
    }

    void move(coords a, float time) {
        currentFrame += 0.1 * time;
        if (currentFrame > 8) {
            currentFrame = 0;
        }
        Pers.loadFromFile("AnimatedPers/_Run.png");
        Sprite.setTexture(Pers);
        Pos.x += a.x * time / 2;
        Sprite.setPosition(Pos.x, Pos.y);
        if (a.x > 0) {
            Sprite.setTextureRect(sf::IntRect(0 + (50 * int(currentFrame)), 30, 30, 52));
        }
        if (a.x < 0) {
            Sprite.setTextureRect(sf::IntRect(0 + (50 * int(currentFrame)) + 30, 30, -30, 52));
        }
        Sprite.setPosition(Pos.x, Pos.y);
    }

    void update(float time) {
        float jumpHeight = 150;
        static float i = 0;
        if (!OnGround) {
            std::cout << "jump" << ' ';
            if (i < jumpHeight) {
                i += 2 * time;
                Pos.y -= 2 * time;
            }
            else
                OnGround = true;
        }
        if (OnGround && Pos.y!= ground) {
            std::cout << "fall" << ' ';
            if (i > 0 ) {
                i -= 2 * time;
                Pos.y += 2 * time;
            }
        }
        Sprite.setPosition(Pos.x, Pos.y);
    }
};

int main()
{
    coords Start_pos{100, 400};
    Character Hero(Start_pos);

    sf::RenderWindow window(sf::VideoMode(1200, 600), "SFML works!");

    sf::Clock clock;

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
           // else
           //     Hero.relax();
        }
       // Hero.update(deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            Hero.move({ 2,0 }, deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            Hero.move({-2,0 }, deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (Hero.OnGround)) {
            Hero.OnGround = false;
        }
        Hero.update(deltaTime);
        window.clear();
        Hero.draw(window);
        window.display();
    }
    return 0;
}