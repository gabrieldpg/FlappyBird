#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Gabijects
{
	class GameOverState : public State
	{
	public:
		// Constructor takes in game data reference and last game's score
		GameOverState(GameDataRef data, int score);

		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		// Sprites for background, title, body, retry button and medal
		sf::Sprite _background;
		sf::Sprite _gameOverTitle;
		sf::Sprite _gameOverContainer;
		sf::Sprite _retryButton;
		sf::Sprite _medal;

		// Text for current score and high score
		sf::Text _scoreText;
		sf::Text _highScoreText;

		// Actual current score and high score
		int _score;
		int _highScore;
	};
}