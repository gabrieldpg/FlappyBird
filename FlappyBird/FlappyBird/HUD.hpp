#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Game.hpp"

namespace Gabijects
{
	class HUD
	{
	public:
		// Constructor takes in game data reference
		HUD(GameDataRef data);

		void Draw();
		void UpdateScore(int score);

	private:
		GameDataRef _data;
		sf::Text _scoreText;
	};
}