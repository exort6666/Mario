#pragma once
#include "Mobs.hpp"
#include "Character.hpp"

namespace MA {
    int  Health = 2;
    bool strike = false;
    bool Saw_hero = false;
    bool TakeDamage = false;
    bool Hitting_Hero = false;
    bool HitPerTime = false;

    Mob::Mob(coords _pos) : MA::Character(_pos) {
        Pos = _pos;
        Enemy.loadFromFile("AnimatedSkeleton/Idle.png");
        SpriteEnemy.setTexture(Enemy);
        SpriteEnemy.setTextureRect(sf::IntRect(45, 95, -45, 55));
        SpriteEnemy.setTextureRect(sf::IntRect(100, 95, -100, 55));
        SpriteEnemy.setPosition(Pos.x, Pos.y);
        DirOfimpact = "left";
        emphasis = false;
    }

    void Mob::draw(sf::RenderWindow& window) {
        window.draw(SpriteEnemy);
    }

    void Mob::update(float distance, float time) {
        static float i = 0;
        //Получение урона//
        if (TakeDamage && Health > 0) {
            Enemy.loadFromFile("AnimatedSkeleton/TakeHit.png");
            SpriteEnemy.setTexture(Enemy);
            currentFrame += 0.01 * time;
            if (currentFrame > 3.5) {
                currentFrame = 0;
                TakeDamage = false;
                Health--;
            }
            if (DirOfimpact == "left")
                SpriteEnemy.setTextureRect(sf::IntRect(100 + 100 * int(currentFrame), 95, -100, 55));
            if (DirOfimpact == "right")
                SpriteEnemy.setTextureRect(sf::IntRect(0 + 100 * int(currentFrame), 95, 100, 55));
        }
        //Смерть//
        if (Health == 0) {
            currentFrame += 0.01 * time;
            Enemy.loadFromFile("AnimatedSkeleton/Death.png");
            SpriteEnemy.setTexture(Enemy);
            if (currentFrame > 3.5) {
                currentFrame = 0;
                Health = -1;
            }
            if (DirOfimpact == "left" && Health == 0) {
                SpriteEnemy.setTextureRect(sf::IntRect(100 + 100 * int(currentFrame), 95, -100, 55));
            }
        }
        //Обнаружение//
        if ((((distance < 100 && distance > -100) || strike) && !TakeDamage) && Health > 0 && hits < 3) {
            Saw_hero = true;
            Hitting_Hero = false;
            Enemy.loadFromFile("AnimatedSkeleton/Idle.png");
            SpriteEnemy.setTexture(Enemy);
            if (DirOfimpact == "right")
                SpriteEnemy.setTextureRect(sf::IntRect(0, 95, 100, 55));
            if (DirOfimpact == "left")
                SpriteEnemy.setTextureRect(sf::IntRect(100, 95, -100, 55));
            //Атака по герою//
            if ((distance < 25 && distance > -25) || strike) {
                if ((distance < 15 && distance > -15) || strike) {
                    currentFrameAttack += 0.025 * time;
                    strike = true;
                    Enemy.loadFromFile("AnimatedSkeleton/Attack.png");
                    SpriteEnemy.setTexture(Enemy);
                    if (currentFrameAttack > 7.5) {
                        currentFrameAttack = 0;
                        strike = false;
                        HitPerTime = true;
                    }
                    if (DirOfimpact == "left") {
                        SpriteEnemy.setTextureRect(sf::IntRect(100 + 100 * (int(currentFrameAttack)), 95, -100, 55));
                        if ((int)currentFrameAttack == 6 && HitDetected(distance) && HitPerTime) {
                            Hitting_Hero = true;
                            HitPerTime = false;
                            hits++;
                        }
                    }
                    if (DirOfimpact == "right") {
                        SpriteEnemy.setTextureRect(sf::IntRect(0 + 100 * (int(currentFrameAttack)), 95, 100, 55));
                        if ((int)currentFrameAttack == 6 && HitDetected(distance) && HitPerTime) {
                            Hitting_Hero = true;
                            HitPerTime = false;
                            hits++;
                        }
                    }
                }
            }
        }
        //Патрулирование//
        if (((distance > 100 || distance < -100) && !strike))
            Saw_hero = false;
        if ((!Saw_hero && !strike) && !TakeDamage && Health > 0) {
            currentFrame += 0.05 * time;
            if (currentFrame > 3.5) {
                currentFrame = 0;
            }
            Enemy.loadFromFile("AnimatedSkeleton/Walk.png");
            SpriteEnemy.setTexture(Enemy);
            if (i < (distanceWalk + 1) && !emphasis) {
                i += 0.25 * time;
                SpriteEnemy.setTextureRect(sf::IntRect(50 + 50 * (int(currentFrame)), 95, -50, 55));
                SpriteEnemy.setTextureRect(sf::IntRect(100 + 100 * (int(currentFrame)), 95, -100, 55));
                Pos.x -= 0.25 * time;
                if (i >= distanceWalk) {
                    emphasis = true;
                }
            }
            if ((i > 0) && emphasis) {
                i -= 0.25 * time;
                SpriteEnemy.setTextureRect(sf::IntRect(0 + 50 * (int(currentFrame)), 95, 50, 55));
                SpriteEnemy.setTextureRect(sf::IntRect(0 + 100 * (int(currentFrame)), 95, 100, 55));
                Pos.x += 0.25 * time;
                if (i < 0)
                    emphasis = false;
            }
        }
        SpriteEnemy.setPosition(Pos.x, Pos.y);
    }

    coords Mob::position() {
        return Pos;
    }
    bool Mob::HitDetected(float distance) {
        if (distance < 15 && distance > -50)
            return true;
        return false;
    }
}