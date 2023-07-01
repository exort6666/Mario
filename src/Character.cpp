#pragma once
#include "Character.hpp"
#include <iostream>
#include <string>
namespace MA {
    Character::Character(coords _pos) :Pos(_pos) {
        Health = 3;
        OnGround = true;
        fall = false;
        strike = false;
        getHit = false;
        alive = true;
        Pers.loadFromFile("AnimatedPers/_Idle.png");
        Sprite.setTexture(Pers);
        Sprite.setTextureRect(sf::IntRect(40, 40, 30, 40));
        Sprite.setPosition(Pos.x, Pos.y);
    }

    void Character::draw(sf::RenderWindow& window) {
        window.draw(Sprite);
    }

    void Character::move(coords a, float time) {
        currentFrame += 0.1 * time;
        if (currentFrame > 8) {
            currentFrame = 0;
        }
        Pers.loadFromFile("AnimatedPers/_Run.png");
        Sprite.setTexture(Pers);
        Pos.x += a.x * time / 2;
        if (a.x > 0) {
            Sprite.setTextureRect(sf::IntRect(0 + (50 * int(currentFrame)), 30, 30, 52));
            DirOfimpact = "right";
        }
        if (a.x < 0) {
            Sprite.setTextureRect(sf::IntRect(0 + (50 * int(currentFrame)) + 30, 30, -30, 52));
            DirOfimpact = "left";
        }
        Sprite.setPosition(Pos.x, Pos.y);
    }

    void Character::update(float time) {
        static float i = 0;
        static float reclining = 0;

        if (Health > 0 && getHit) {
            Pers.loadFromFile("AnimatedPers/Hit.png");
            Sprite.setTexture(Pers);
            if (DirOfimpact == "right" && reclining < 51) {
                reclining += 0.25 * time;
                Pos.x -= 0.25 * time;
                Sprite.setTextureRect(sf::IntRect(30, 40, -30, 40));
                if (reclining > 50) {
                    reclining = 0;
                    getHit = false;
                    currentFrame = 0;
                }
            }
            if (DirOfimpact == "left" && reclining > -51) {
                reclining -= 0.25 * time;
                Pos.x += 0.25 * time;
                getHit = false;
                Sprite.setTextureRect(sf::IntRect(0, 40, 30, 40));
                if (reclining < -50) {
                    reclining = 0;
                    getHit = false;
                    currentFrame = 0;
                }
            }
        }
        if (Health == 0 && alive) {
            Pers.loadFromFile("AnimatedPers/Death.png");
            Sprite.setTexture(Pers);
            currentFrame += 0.05 * time;
            std::cout << currentFrame << std::endl;
            if (DirOfimpact == "right"){
                Sprite.setTextureRect(sf::IntRect(0 + (50 * int(currentFrame)), 40, 40, 40));
            }
            if (DirOfimpact == "left")
                Sprite.setTextureRect(sf::IntRect(50 + (50 * int(currentFrame)), 40, -50, 40));
            if ((int)currentFrame > 9)
                alive = false;
        }
        if (!OnGround && !fall && !getHit && Health > 0) {
            Pers.loadFromFile("AnimatedPers/_Jump.png");
            Sprite.setTexture(Pers);
            if (DirOfimpact == "right")
                Sprite.setTextureRect(sf::IntRect(40, 40, 30, 40));
            if (DirOfimpact == "left")
                Sprite.setTextureRect(sf::IntRect(80, 40, -40, 40));
            if (i < jumpHeight) {
                i += 2 * time;
                Pos.y -= 2 * time;
            }
            else {
                OnGround = true;
                fall = true;
            }
        }
        if (OnGround && Pos.y != 400 && fall && !getHit && Health > 0) {
            if (i >= 0) {
                i -= 2 * time;
                Pos.y += 2 * time;
            }
            else {
                fall = false;
                i = 0;
            }
        }
        if (strike && !getHit && Health > 0) {
            Pers.loadFromFile("AnimatedPers/_Attack.png");
            Sprite.setTexture(Pers);
            currentFrameAttack += 0.02 * time;
            if (currentFrameAttack > 4) {
                currentFrameAttack = 0;
                strike = false;
            }
            if (DirOfimpact == "right")
                Sprite.setTextureRect(sf::IntRect(0 + (70 * int(currentFrameAttack)), 40, 70, 40));
            if (DirOfimpact == "left")
                Sprite.setTextureRect(sf::IntRect(0 + (70 * int(currentFrameAttack)) + 70, 40, -70, 40));
        }
        Sprite.setPosition(Pos.x, Pos.y);
    }

    void Character::attack() {
        if (!strike && !fall && OnGround) {
            strike = true;
        }
    }

    Character::~Character() = default;
}