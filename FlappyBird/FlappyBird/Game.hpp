#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"


namespace Gabijects
{
	// Structure of all essential game data
	struct GameData
	{
		StateMachine machine;		// state machine, responsible for state management
		sf::RenderWindow window;	// sfml window, responsible for displaying game
		AssetManager assets;		// asset manager, responsible for loading and storing assets
		InputManager input;			// input manager, detects input
	};

	// Shared pointer of game data which will be shared among classes
	typedef std::shared_ptr<GameData> GameDataRef;

	class Game
	{
	public:
		// Initialise game with screen width, height, and game title
		Game(int width, int height, std::string title);

	private:
		const float dt = 1.0f / 60.0f;		// delta timing, used for speed consistency
		sf::Clock _clock;

		GameDataRef _data = std::make_shared<GameData>();	// reference to game data

		// Run the game
		void Run();
	};
}