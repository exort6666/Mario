#pragma once
#define CHARACTER_H
#include <SFML/Graphics.hpp>

struct coords {
    float x;
    float y;
};

//int ground = 400;

class Character {
private:
    sf::Texture Pers;
    sf::Sprite Sprite;
    coords Pos;
    double currentFrame = 0;
    float currentFrameAttack = 0;
    float jumpHeight = 100;
    std::string DirOfimpact;

public:
    bool strike;
    bool OnGround;
    bool fall; 

    Character(coords _pos);
    
    void draw(sf::RenderWindow& window);

    void move(coords a, float time);

    void update(float time);

    void attack();
};
