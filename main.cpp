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
     
    float currentFrame = 0;
    float currentFrameAttack = 0;
    float HitRange = 15;
    float distanceWalk = 150;

    std::string DirOfimpact;
    bool emphasis;

public:
    int Health = 2;
    bool Strike;
    bool Saw_hero = false;
    bool TakeDamage = false;

    Mob(coords _pos): Character(_pos) {
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
        if(TakeDamage && Health > 0) {
            Enemy.loadFromFile("AnimatedSkeleton/TakeHit.png");
            SpriteEnemy.setTexture(Enemy);
            currentFrame += 0.01 * time;
            if (currentFrame > 3){
                currentFrame = 0;
                TakeDamage = false;
                Health--;
            }
            if (DirOfimpact == "left") {
                SpriteEnemy.setTextureRect(sf::IntRect(50 + 50 * int(currentFrame), 95, -50, 55));
            }
        }
        if (Health == 0) {
            currentFrame += 0.01 * time;
            Enemy.loadFromFile("AnimatedSkeleton/Death.png");
            SpriteEnemy.setTexture(Enemy);
            if(currentFrame > 3.5) {
                currentFrame = 0;
                Health = -1;
            }
            if (DirOfimpact == "left" && Health == 0) {
                SpriteEnemy.setTextureRect(sf::IntRect(100 + 100 * int(currentFrame), 95, -100, 55));
            }
        }
        if ((((distance < 100 && distance > -100) || strike) && !TakeDamage) && Health > 0) {
            Saw_hero = true;
            Enemy.loadFromFile("AnimatedSkeleton/Idle.png");
            SpriteEnemy.setTexture(Enemy);
            if (DirOfimpact == "right")
                SpriteEnemy.setTextureRect(sf::IntRect(0, 95, 45, 55));
            if (DirOfimpact == "left")
                SpriteEnemy.setTextureRect(sf::IntRect(45, 95, -45, 55));
            if ((distance < 25 && distance > -25) || strike) {
                currentFrameAttack += 0.025 * time;
                strike = true;
                Enemy.loadFromFile("AnimatedSkeleton/Attack.png");
                SpriteEnemy.setTexture(Enemy);
                if (currentFrameAttack > 7) {
                    currentFrameAttack = 0;
                    strike = false;
                }
                if (DirOfimpact == "left") {
                    SpriteEnemy.setTextureRect(sf::IntRect(100 + 100 * (int(currentFrameAttack)), 95, -100, 55));
                }
                if (DirOfimpact == "right") {
                    SpriteEnemy.setTextureRect(sf::IntRect(0 + 100 * (int(currentFrameAttack)), 95, 80, 55));
                }
            }
        }

        if (((distance > 100 || distance < -100) && !strike) && !TakeDamage && Health > 0)
            Saw_hero = false;

        if ((!Saw_hero && !strike)&& !TakeDamage && Health > 0) {
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
        }
        SpriteEnemy.setPosition(Pos.x, Pos.y);
    }

    coords position() {
        return Pos;
    }
};

int main()
{
    std::unique_ptr<Character> Hero(new Character({100,400}));
    std::unique_ptr<Mob> Skeleton(new Mob({ 700,400 }));

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
            if ((Hero->position().x - Skeleton->position().x <= 15)&& Skeleton->Health != 0) {
                Skeleton->TakeDamage = true;
            }
        }
        Hero->update(deltaTime);
        Skeleton->update((Skeleton->position().x - Hero->position().x), deltaTime);
        window.clear();

        Hero->draw(window);
        Skeleton->draw(window);

        window.display();
        }
    return 0;
}