#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Gabijects
{
	class MainMenuState : public State
	{
	public:
		// Constructor takes in game data reference
		MainMenuState(GameDataRef data);

		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;
		// Sprites for background image, title image and play button image
		sf::Sprite _background;
		sf::Sprite _title;
		sf::Sprite _playButton;
	};
}