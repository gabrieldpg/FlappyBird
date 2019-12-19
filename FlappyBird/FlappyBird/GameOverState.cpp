#include <sstream>
#include "GameOverState.hpp"
#include "DEFINITIONS.hpp"
#include "GameState.hpp"
#include <iostream>
#include <fstream>

namespace Gabijects
{
	// constructor saves game data reference and last game's score
	GameOverState::GameOverState(GameDataRef data, int score) : _data(data), _score(score) { }

	void GameOverState::Init()
	{
		// open high score text file to read
		std::ifstream readFile;
		readFile.open(HIGHSCORE_FILEPATH);

		// if it can be read
		if (readFile.is_open())
		{
			// whie file not finished, read in high score value
			while (!readFile.eof())
			{
				readFile >> _highScore;
			}
		}

		// close read file
		readFile.close();

		// open high score file to write
		std::ofstream writeFile(HIGHSCORE_FILEPATH);

		// if it opens successfully
		if (writeFile.is_open())
		{
			// and last game;s score is higher than current high score
			if (_score > _highScore)
			{
				// change high score to last game's score
				_highScore = _score;
			}
			// save high score to file
			writeFile << _highScore;
		}

		// close write file
		writeFile.close();

		// load textures for game over background, title and body
		_data->assets.LoadTexture("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH);
		_data->assets.LoadTexture("Game Over Title", GAME_OVER_TITLE_FILEPATH);
		_data->assets.LoadTexture("Game Over Body",	GAME_OVER_BODY_FILEPATH);

		// load textures for medals
		_data->assets.LoadTexture("Bronze Medal", BRONZE_MEDAL_FILEPATH);
		_data->assets.LoadTexture("Silver Medal", SILVER_MEDAL_FILEPATH);
		_data->assets.LoadTexture("Gold Medal", GOLD_MEDAL_FILEPATH);
		_data->assets.LoadTexture("Platinum Medal", PLATINUM_MEDAL_FILEPATH);

		// set textures for background, title, body and retry button
		_background.setTexture(this->_data->assets.GetTexture("Game Over Background"));
		_gameOverTitle.setTexture(this->_data->assets.GetTexture("Game Over Title"));
		_gameOverContainer.setTexture(this->_data->assets.GetTexture("Game Over Body"));
		_retryButton.setTexture(this->_data->assets.GetTexture("Play Button"));

		// set game over body to be centred in the x and y axis
		_gameOverContainer.setPosition((_data->window.getSize().x / 2) - (_gameOverContainer.getGlobalBounds().width / 2),
			(_data->window.getSize().y / 2) - (_gameOverContainer.getGlobalBounds().height / 2));
		// set game over title to be centred in the x axis and above body by its heigh and a bit
		_gameOverTitle.setPosition((_data->window.getSize().x / 2) - (_gameOverTitle.getGlobalBounds().width / 2), 
			_gameOverContainer.getPosition().y - (_gameOverTitle.getGlobalBounds().height * 1.2));
		// set retry button to be centred in the x axis and below body by its own height and a bit
		_retryButton.setPosition((_data->window.getSize().x / 2) - (_retryButton.getGlobalBounds().width / 2),
			_gameOverContainer.getPosition().y + _gameOverContainer.getGlobalBounds().height + (_retryButton.getGlobalBounds().height * 0.2));

		// set score text's font, its string to last game's score, its character size and color
		_scoreText.setFont(_data->assets.GetFont("Flappy Font"));
		_scoreText.setString(std::to_string(_score));
		_scoreText.setCharacterSize(56);
		_scoreText.setFillColor(sf::Color::White);
		// set score text's origin to be in its centre and its
		// position to be under score in game over container/body
		_scoreText.setOrigin(_scoreText.getGlobalBounds().width / 2, _scoreText.getGlobalBounds().height / 2);
		_scoreText.setPosition(_data->window.getSize().x / 10 * 7.25, _data->window.getSize().y / 2.15);

		// set high score text's font, its string to the high score, its character size and color
		_highScoreText.setFont(_data->assets.GetFont("Flappy Font"));
		_highScoreText.setString(std::to_string(_highScore));
		_highScoreText.setCharacterSize(56);
		_highScoreText.setFillColor(sf::Color::White);
		// set high score text's origin to be in its centre and its
		// position to be under high score in game over container/body
		_highScoreText.setOrigin(_highScoreText.getGlobalBounds().width / 2, _highScoreText.getGlobalBounds().height / 2);
		_highScoreText.setPosition(_data->window.getSize().x / 10 * 7.25, _data->window.getSize().y / 1.78);

		// check if last game's score was worth a Bronze, Silver, Gold
		// or Platinum medal and set medal's texture to it accordingly
		if (_score >= PLATINUM_MEDAL_SCORE)
		{
			_medal.setTexture(_data->assets.GetTexture("Platinum Medal"));
		}
		else if (_score >= GOLD_MEDAL_SCORE)
		{
			_medal.setTexture(_data->assets.GetTexture("Gold Medal"));
		}
		else if (_score >= SILVER_MEDAL_SCORE)
		{
			_medal.setTexture(_data->assets.GetTexture("Silver Medal"));
		} 
		else
		{
			_medal.setTexture(_data->assets.GetTexture("Bronze Medal"));
		}

		// set medal's position to be under medal in game over container/body
		_medal.setPosition(175, 465);
	}

	void GameOverState::HandleInput()
	{
		sf::Event event;

		// while there are events in window
		while (_data->window.pollEvent(event))
		{
			// if event is closed, then close window
			if (event.type == sf::Event::Closed)
			{
				_data->window.close();
			}
			// if retry button been clicked with left mouse button in window
			if (_data->input.IsSpriteClicked(_retryButton, sf::Mouse::Left, _data->window))
			{
				// then replace state with game state again
				_data->machine.AddState(StateRef(new GameState(_data)), true);
			}
		}
	}

	void GameOverState::Update(float dt)
	{
		// nothing to be updated in this state
	}

	void GameOverState::Draw(float dt)
	{
		// clear window
		_data->window.clear();

		// draw background, title, container, retry button, score, high score and medal
		_data->window.draw(_background);
		_data->window.draw(_gameOverTitle);
		_data->window.draw(_gameOverContainer);
		_data->window.draw(_retryButton);
		_data->window.draw(_scoreText);
		_data->window.draw(_highScoreText);
		_data->window.draw(_medal);

		// display in window
		_data->window.display();
	}
}