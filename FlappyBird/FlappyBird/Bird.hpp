#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Game.hpp"
#include <vector>

namespace Gabijects
{
	class Bird
	{
	public:
		Bird(GameDataRef data);

		void Draw();
		void Animate(float dt);
		void Update(float dt);
		void Tap();

	private:
		GameDataRef _data;
		sf::Sprite _birdSprite;
		int _birdState;

		std::vector<sf::Texture> _animationFrames;
		unsigned int _animationIterator;

		sf::Clock _clock;
		sf::Clock _movementClock;
	};
}