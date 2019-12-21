#include "Collision.hpp"

namespace Gabijects
{
	// nothing to construct
	Collision::Collision() {}

	bool Collision::CheckSpriteCollision(sf::Sprite sprite1, sf::Sprite sprite2)
	{
		// get rectangle object for each sprite
		sf::Rect<float> rect1 = sprite1.getGlobalBounds();
		sf::Rect<float> rect2 = sprite2.getGlobalBounds();

		// if they intersect each other, return true, otherwise false
		if (rect1.intersects(rect2))
		{
			return true;
		}
		return false;
	}

	bool Collision::CheckSpriteCollision(sf::Sprite sprite1, float scale1, sf::Sprite sprite2, float scale2)
	{
		// set sprites' scales
		sprite1.setScale(scale1, scale1);
		sprite2.setScale(scale2, scale2);

		// get rectangle object for each sprite
		sf::Rect<float> rect1 = sprite1.getGlobalBounds();
		sf::Rect<float> rect2 = sprite2.getGlobalBounds();

		// if they intersect each other, return true, otherwise false
		if (rect1.intersects(rect2))
		{
			return true;
		}
		return false;
	}
}