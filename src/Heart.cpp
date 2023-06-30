#include "Heart.hpp"
namespace MA {
	Heart::Heart() = default;
	Heart::Heart(coords coord) : MA::Object(coord) {
		m_coords = coord;
		sf::Vector2f targetSize(20.0f, 20.0f); //целевой размер
		Texture.loadFromFile("Heart/Full.png");
		Sprite.setTexture(Texture);
		Sprite.setTextureRect(sf::IntRect(50, 50, 260, 220));
		Sprite.setPosition(m_coords.x, m_coords.y);
		Sprite.setScale(
			targetSize.x / Sprite.getLocalBounds().width,
			targetSize.y / Sprite.getLocalBounds().height);
	}
	void Heart::draw(sf::RenderWindow& window) {
		window.draw(Sprite);
	}
	void Heart::setCoords(coords coord){
		m_coords = coord;
		Sprite.setPosition(coord.x, coord.y);
	}
	coords Heart::getCoords() {
		return(m_coords);
	}
}