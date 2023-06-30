/*#pragma once
#include "Character.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Mob: public Character {
private:
    sf::Texture Enemy;
    sf::Sprite SpriteEnemy;
    coords Pos;
    double currentFrame = 0;
    float currentFrameAttack = 0;
    float HitRange = 15;
    std::string DirOfimpact;

public:
    bool strike;
    Mob(coords _pos): Character(_pos) {
        Enemy.loadFromFile("AnimatedSkeleton/Idle.png");
        SpriteEnemy.setTexture(Enemy);
        SpriteEnemy.setTextureRect(sf::IntRect(45, 95, -45, 100));
        SpriteEnemy.setPosition(Pos.x, Pos.y);
        DirOfimpact = "left";
    }
    
    void draw(sf::RenderWindow& window) override{
        window.draw(SpriteEnemy);
    }


    void move(coords a, float time)
    {

    }
};*/
