#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Pipe.hpp"
#include "Land.hpp"
#include "Bird.hpp"
#include "Collision.hpp"
#include "Flash.hpp"
#include "HUD.hpp"

namespace Gabijects
{
	class GameState : public State
	{
	public:
		// Constructor takes in game data reference
		GameState(GameDataRef data);

		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;
		sf::Sprite _background;		// sprite which holds background

		// pointers to pipes, land and bird
		Pipe *pipe;
		Land *land;
		Bird *bird;

		Collision collision;	// collision detection
		Flash *flash;			// flash for game over
		HUD *hud;				// heads up display

		sf::Clock _clock;

		int _gameState;			// game state currently (eg ready, playing, gameover)
		int _score;				// score at certain point in time in game
	};
}