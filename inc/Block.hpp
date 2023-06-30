#pragma once
#include <Object.hpp>
#include "Character.hpp"
namespace MA {
	class Block : public MA::Object
	{
	private:
		sf::RectangleShape* m_rectangle = nullptr;
		int m_thicknessOutline = 10;
		sf::Color m_colorOutline = sf::Color::Blue;
		coords m_size = { 50,50 };
	public:
		Block();
		Block(coords coords,sf::Color color);
		void Block::setSize(coords size);
		coords Block::getSize();
		void Block::setOutlinecolor(sf::Color color);
		sf::Color Block::getOutlinecolor();
		void Block::setOutlineThickness(int thicknessOutline);
		int Block::getOutlineThichness();
		void draw(sf::RenderWindow& window);
		~Block();
	};
}