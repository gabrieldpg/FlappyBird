#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <vector>

namespace Gabijects
{
	class Land
	{
	public:
		// Constructor takes in game data reference
		Land(GameDataRef data);

		// Move land to the left
		void MoveLand(float dt);
		void DrawLand();

		// Get constant reference to land sprites
		const std::vector<sf::Sprite> &GetSprites() const;

	private:
		GameDataRef _data;
		std::vector<sf::Sprite> _landSprites;
	};
}