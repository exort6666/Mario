#include "Character.hpp"
//#include "Mobs.hpp"
#include <iostream>
#include <chrono>
#include <thread>

class Mob : public Character{
private:
    sf::Texture Enemy;
    sf::Sprite SpriteEnemy;
    coords Pos;
    double currentFrame = 0;
    float currentFrameAttack = 0;
    float HitRange = 15;
    std::string DirOfimpact;
    float distanceWalk = 75;
    bool emphasis;

public:
    bool Strike;
    bool Saw_hero = false;
    Mob(coords _pos): Character(_pos){
        Pos = _pos;
        Enemy.loadFromFile("AnimatedSkeleton/Idle.png");
        SpriteEnemy.setTexture(Enemy);
        SpriteEnemy.setTextureRect(sf::IntRect(45, 95, -45, 55));
        SpriteEnemy.setPosition(Pos.x, Pos.y);
        DirOfimpact = "left";
        emphasis = false;
    }

    void draw(sf::RenderWindow& window){
        window.draw(SpriteEnemy);
    }

    void update(float distance,float time) {
        static float i = 0;
        if (distance < 150) {
            Saw_hero = true;
        }
        if (!Saw_hero) {
            currentFrame += 0.05 * time;
            if (currentFrame > 3) {
                currentFrame = 0;
            }
            Enemy.loadFromFile("AnimatedSkeleton/Walk.png");
            SpriteEnemy.setTexture(Enemy);
            if (i < (distanceWalk + 1) && !emphasis) {
                i += 0.25 * time;
                SpriteEnemy.setTextureRect(sf::IntRect(50 + 50 * (int(currentFrame)), 95, -50, 55));
                Pos.x -= 0.25 * time;
                if (i >= distanceWalk) {
                    emphasis = true;
                }
            }
            if ((i > 0) && emphasis) {
                i -= 0.25 * time;
                SpriteEnemy.setTextureRect(sf::IntRect(0 + 50 * (int(currentFrame)), 95, 50, 55));
                Pos.x += 0.25 * time;
                if (i < 0)
                    emphasis = false;
            }
            SpriteEnemy.setPosition(Pos.x, Pos.y);
            std::cout << i << ' ' << emphasis << std::endl;
        }
    }

    coords position() {
        return Pos;
    }


    void move(coords a, float time)
    {

    }

    bool takeDamage(float range)
    {
        if (Pos.x - range <= 15) {
            return true;
        }
        else
            return false;
    }
};

int main()
{
    Character* Hero =  new  Character({ 100, 400 });
    Mob* Skeleton = new Mob({ 700, 400 });

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
            Hero->move({ 2,0 }, deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            Hero->move({ -2,0 }, deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (Hero->OnGround) && (!Hero->fall))
            Hero->OnGround = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && (!Hero->strike) && (!Hero->fall) && (Hero->OnGround)){
            Hero->attack();
            if (Skeleton->takeDamage((Hero->position().x))) {
                //Добавить функцию получения по ебалу//
            }
        }
        Hero->update(deltaTime);
        Skeleton->update((Skeleton->position().x - Hero->position().x), deltaTime);
        //Добавить получение по ебучке герою//
        window.clear();

        Hero->draw(window);
        Skeleton->draw(window);

        window.display();
        }
    return 0;
}