#pragma once
#include <SFML/Graphics.hpp>
class Object
{
private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
public:
	Object();
	Object(sf::Sprite sprite, sf::Texture texture);
};