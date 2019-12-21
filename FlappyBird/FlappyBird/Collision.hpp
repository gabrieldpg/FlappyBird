#pragma once

#include <SFML/Graphics.hpp>

namespace Gabijects
{
	class Collision
	{
	public:
		Collision();

		// Check if sprites are colliding
		bool CheckSpriteCollision(sf::Sprite sprite1, sf::Sprite sprite2);
		// Check if sprites are colliding, using a scale
		bool CheckSpriteCollision(sf::Sprite sprite1, float scale1, sf::Sprite sprite2, float scale2);
	};
}