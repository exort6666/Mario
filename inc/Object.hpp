#pragma once
#include <SFML/Graphics.hpp>
#include "Character.hpp"
namespace MA {
	class Object
	{
	private:
		coords m_coords;
		sf::Color m_color;
	public:
		Object();
		Object(coords coords);
		Object(sf::Color color);
		Object(coords coords, sf::Color color);
		virtual void setCoords(coords coords);
		virtual coords getCoords();
		void setColor(sf::Color color);
		sf::Color getColor();
		~Object();
	};
}