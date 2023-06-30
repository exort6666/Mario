#include "Character.hpp"
#include "Block.hpp"
#include "Heart.hpp"
//#include "Mobs.hpp"
#include <iostream>
#include <chrono>
#include <thread>

class Mob : public Character{
private:
    sf::Texture Enemy;
    sf::Sprite SpriteEnemy;
    coords Pos;
     
    int Health = 2;
    float currentFrame = 0;
    float currentFrameAttack = 0;
    float HitRange = 15;
    float distanceWalk = 150;

    std::string DirOfimpact;
    bool emphasis;

public:
    bool Strike;
    bool Saw_hero = false;
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
        if ((distance < 100 && distance > -100) || strike) {
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
                if (DirOfimpact == "left")
                    SpriteEnemy.setTextureRect(sf::IntRect(100 + 100 * (int(currentFrameAttack)), 95, -100, 55));
                if (DirOfimpact == "right")
                    SpriteEnemy.setTextureRect(sf::IntRect(0 + 100 * (int (currentFrameAttack)), 95, 80, 55));
            }
        }
        if ((distance > 100 && distance < -100) && !strike)
            Saw_hero = false;
        if (!Saw_hero && !strike) {
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

    bool takeDamage(float range) {
        if (Pos.x - range <= 15) {
            return true;
        }
        else
            return false;
    }
};

int main()
{
 
    // Позиция блоков
    coords Block_pos;
    // Выбирается цвет блоков
    sf::Color color_blocks = sf::Color::Black;

    // Всё для бэкграунда
    sf::Texture background;
    background.loadFromFile("Background/background.png");
    sf::Sprite backgrounds(background);

    Character* Hero =  new  Character({ 100, 400 });
    Mob* Skeleton = new Mob({ 700, 400 });
    // Создаются размеры окна
    coords Field{ 1200, 600 };
    sf::RenderWindow window(sf::VideoMode(Field.x, Field.y), "SFML works!");
    // Создается сердце
    coords heart_pos = { 0,0 };
    MA::Heart heart(heart_pos);
    sf::Clock clock;
    // Количество ударов,получаемое героем
    int hit = 0;
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


            }
        }
        Hero->update(deltaTime);
        Skeleton->update((Skeleton->position().x - Hero->position().x), deltaTime);
        //Добавить получение по ебучке герою//
        window.clear();
        //Бэкграунд
        window.draw(backgrounds);
        //Выбираются позиции блоков и рисуются
        Block_pos = { 0, 460 };
        while (Block_pos.y < Field.y) {
            while (Block_pos.x < Field.x) {
                MA::Block Block(Block_pos, color_blocks);
                Block.draw(window);
                Block_pos.x += 50;
            }
            Block_pos.x = 0;
            Block_pos.y += 50;
        }
        coords heart_pos = { 0,0 };
        for (int i = 0; i < 5 - hit; i++) {
            heart.draw(window);
            heart_pos.x += 20;
            heart.setCoords(heart_pos);
        }
        Hero->draw(window);
        Skeleton->draw(window);

        window.display();
        }
    return 0;
}