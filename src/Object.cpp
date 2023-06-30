#include <SFML/Graphics.hpp>
#include <Object.hpp>
namespace MA {
	// ������������
	// ������� �����������
	Object::Object() = default;
	// ����������� �� �����������
	Object::Object(coords coords) {
		m_coords = coords;
	}
	// ����������� �� �����(�� ������)
	Object::Object(sf::Color color) {
		m_color = color;
	}
	// ���������� �� ����������� � �����
	Object::Object(coords coords, sf::Color color) {
		m_coords = coords;
		m_color = color;
	}

	//							�������,�������:
	//	1) ���������
	void Object::setCoords(coords coords)
	{
		m_coords = coords;
	}
	coords Object::getCoords() 
	{
		return(m_coords);
	}
	//	2) �����
	void Object::setColor(sf::Color color)
	{
		m_color = color;
	}
	sf::Color Object::getColor() 
	{
		return(m_color);
	}
	// ����������
	Object::~Object() = default;
}