#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Gabijects
{
	class SplashState : public State
	{
	public:
		// Constructor takes in game data reference
		SplashState(GameDataRef data);

		void Init();
		void HandleInput();	
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;
		sf::Clock _clock;
		sf::Sprite _background;		// sprite with background image
	};
}