#include <Block.hpp>
namespace MA {
	// Конструкторы
	// 1) По умолчанию
	Block::Block() = default;
	// 2) по позиции и цвету
	Block::Block(coords coords,sf::Color color_rectangle) : MA::Object(coords,color_rectangle) {
		m_rectangle = new sf::RectangleShape;
		m_rectangle->setSize(sf::Vector2f(m_size.x,m_size.y));
		m_rectangle->setPosition(coords.x, coords.y);
		m_rectangle->setFillColor(color_rectangle);
		//Задаю контуры
		m_rectangle->setOutlineThickness(m_thicknessOutline);
		m_rectangle->setOutlineColor(sf::Color(m_colorOutline));
	}
	//						Сеттеры,геттеры
	// 1) Размер
	void Block::setSize(coords size) {
		m_size = size;
	}
	coords Block::getSize() {
		return(m_size);
	}
	// 2) Цвет контура
	void Block::setOutlinecolor(sf::Color color) {
		m_colorOutline = color;
	}
	sf::Color Block::getOutlinecolor() {
		return (m_colorOutline);
	}
	// 3) Размер контура
	void Block::setOutlineThickness(int thicknessOutline) {
		m_thicknessOutline = thicknessOutline;
	}
	int Block::getOutlineThichness() {
		return (m_thicknessOutline);
	}
	// Вывод блока
	void Block::draw(sf::RenderWindow& window) {
		window.draw(*m_rectangle);
	}
	// Деструктор
	Block::~Block() 
	{
		if (m_rectangle != nullptr)
			delete m_rectangle;
	}
}
