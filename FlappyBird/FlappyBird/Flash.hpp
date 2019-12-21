#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "DEFINITIONS.hpp"

namespace Gabijects
{
	class Flash
	{
	public:
		// Constructor takes in game data reference
		Flash(GameDataRef data);

		void Show(float dt);
		void Draw();

	private:
		GameDataRef _data;
		sf::RectangleShape _shape;
		bool _flashOn;				// used to differentiate when flash getting brighter or darker
	};
}