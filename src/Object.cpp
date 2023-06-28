#include "Object.hpp"
class Object
{
private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
public:
	Object() = default;
	Object(sf::Sprite sprite, sf::Texture texture) {
		m_sprite = sprite;
		m_texture = texture;
	}
};