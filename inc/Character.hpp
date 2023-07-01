#pragma once
#define CHARACTER_H
#include <SFML/Graphics.hpp>

struct coords {
    float x;
    float y;
};
namespace MA {
    class Character {
    private:
        sf::Texture Pers;
        sf::Sprite Sprite;
        double currentFrame = 0;
        float currentFrameAttack = 0;
        float jumpHeight = 150;
        float HitRange = 15;
        coords Pos;
        bool alive;

    public:
        int Health;
        bool strike;
        bool OnGround;
        bool fall;
        bool getHit;

        Character(coords _pos);

        virtual void draw(sf::RenderWindow& window);

        virtual void move(coords a, float time);

        virtual void update(float time);

        virtual void attack();

        virtual coords position() {
            return Pos;
        };
        virtual ~Character();
    protected:
        std::string DirOfimpact = "right";
    };
}