#pragma once
#include "Character.hpp"
#include "Object.hpp"
namespace MA {
	class Heart: public MA::Object
	{
	private:
		coords m_coords;
		sf::Texture Texture;
		sf::Sprite Sprite;
	public:
		Heart();
		Heart(coords cords);
		void draw(sf::RenderWindow& window);
		void setCoords(coords coord) override;
		coords getCoords() override;
	};
}