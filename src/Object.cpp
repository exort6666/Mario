#include <SFML/Graphics.hpp>
#include <Object.hpp>
namespace MA {
	// Конструкторы
	// Базовый конструктор
	Object::Object() = default;
	// Конструктор по координатам
	Object::Object(coords coords) {
		m_coords = coords;
	}
	// Конструктор по цвету(на всякий)
	Object::Object(sf::Color color) {
		m_color = color;
	}
	// Констуктор по координатам и цвету
	Object::Object(coords coords, sf::Color color) {
		m_coords = coords;
		m_color = color;
	}

	//							Геттеры,сеттеры:
	//	1) Координат
	void Object::setCoords(coords coords)
	{
		m_coords = coords;
	}
	coords Object::getCoords() 
	{
		return(m_coords);
	}
	//	2) Цвета
	void Object::setColor(sf::Color color)
	{
		m_color = color;
	}
	sf::Color Object::getColor() 
	{
		return(m_color);
	}
	// Деструктор
	Object::~Object() = default;
}