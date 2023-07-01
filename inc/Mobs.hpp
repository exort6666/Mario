#pragma once
#include "Character.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

namespace MA {
    class Mob : public MA::Character {
    private:
        sf::Texture Enemy;
        sf::Sprite SpriteEnemy;
        coords Pos;

        int hits = 0;
        float currentFrame = 0;
        float currentFrameAttack = 0;
        float HitRange = 15;
        float distanceWalk = 150;

        std::string DirOfimpact;
        bool emphasis;

    public:
        int  Health;
        bool strike;
        bool Saw_hero;
        bool TakeDamage;
        bool Hitting_Hero;
        bool HitPerTime;

        Mob(coords _pos) : MA::Character(_pos) {}

        void draw(sf::RenderWindow& window) {};

        void update(float distance, float time) {};

        coords position() {};

        bool HitDetected(float distance) {};
    };
}