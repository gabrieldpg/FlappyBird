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
		// Constructor takes in game data reference
		Bird(GameDataRef data);

		void Draw();
		void Animate(float dt);
		void Update(float dt);

		// Method indicating bird has to fly
		void Tap();

		// Returns constant reference to bird sprite
		const sf::Sprite &GetSprite() const;

	private:
		GameDataRef _data;

		sf::Sprite _birdSprite;
		int _birdState;			// Indicates if bird is still, flying or falling
		float _rotation;		// Indicates rotation of bird

		std::vector<sf::Texture> _animationFrames;	// Vector with different bird frame textures
		unsigned int _animationIterator;

		sf::Clock _clock;			// used for changing animation frames
		sf::Clock _movementClock;	// used for timing bird's flying time
	};
}