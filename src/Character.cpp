#pragma once
#include "Character.hpp"

Character::Character(coords _pos):Pos(_pos) {
    OnGround = true;
    Pers.loadFromFile("AnimatedPers/Comparison2x.png");
    Sprite.setTexture(Pers);
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
    Sprite.setPosition(Pos.x, Pos.y);
    if (a.x > 0) {
        Sprite.setTextureRect(sf::IntRect(0 + (50 * int(currentFrame)), 30, 30, 52));
    }
    if (a.x < 0) {
        Sprite.setTextureRect(sf::IntRect(0 + (50 * int(currentFrame)) + 30, 30, -30, 52));
    }
    Sprite.setPosition(Pos.x, Pos.y);
}

void Character::update(float time) {
    float jumpHeight = 150;
    static float i = 0;
    if (!OnGround) {
        if (i < jumpHeight) {
            i += 2 * time;
            Pos.y -= 2 * time;
        }
        else
            OnGround = true;
    }
    if (OnGround && Pos.y != 400/*ground*/) {
        if (i >= 0) {
            i -= 2 * time;
            Pos.y += 2 * time;
        }
    }
    Sprite.setPosition(Pos.x, Pos.y);
}