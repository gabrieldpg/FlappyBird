#include <sstream>
#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace Gabijects
{
	// constructor saves game data reference
	MainMenuState::MainMenuState(GameDataRef data) : _data(data) {}

	void MainMenuState::Init()
	{
		// load texture for all sprites
		_data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
		_data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);
		_data->assets.LoadTexture("Play Button",PLAY_BUTTON_FILEPATH);

		// set all sprites' texture
		_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
		_title.setTexture(this->_data->assets.GetTexture("Game Title"));
		_playButton.setTexture(this->_data->assets.GetTexture("Play Button"));

		// set position of title to be centred in the x axis and 
		// to be on top on the y axis, but slightly down by half its height
		_title.setPosition((SCREEN_WIDTH / 2) - (_title.getGlobalBounds().width / 2),
			_title.getGlobalBounds().height / 2);
		// set posotion of play button to be centred
		// in the x axis and as well as in the y axis
		_playButton.setPosition((SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - (_playButton.getGlobalBounds().height / 2));

	}

	void MainMenuState::HandleInput()
	{
		sf::Event event;

		// while there are events on window
		while (_data->window.pollEvent(event))
		{
			// if the event is to close, then close window
			if (event.type == sf::Event::Closed)
			{
				_data->window.close();
			}
			// if the play button has been clicked with the left mouse on the window
			if (_data->input.IsSpriteClicked(_playButton, sf::Mouse::Left, _data->window))
			{
				// replace main menu state with game state in states stack
				_data->machine.AddState(StateRef(new GameState(_data)), true);
			}
		}
	}

	void MainMenuState::Update(float dt)
	{
		// no updates required on this state
	}

	void MainMenuState::Draw(float dt)
	{
		// clear window, draw sprites and display
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.draw(_title);
		_data->window.draw(_playButton);
		_data->window.display();
	}
}