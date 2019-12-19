#include <sstream>
#include "SplashState.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace Gabijects
{
	// constructor saves game data reference
	SplashState::SplashState(GameDataRef data) : _data(data) {}

	void SplashState::Init()
	{
		// load splash state background picture and set bacground texture to it
		_data->assets.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
		_background.setTexture(this->_data->assets.GetTexture("Splash State Background"));
	}

	void SplashState::HandleInput()
	{
		sf::Event event;

		// while there are events in the window
		while (_data->window.pollEvent(event))
		{
			// if the event type is closed, close the window
			if (event.type == sf::Event::Closed)
			{
				_data->window.close();
			}
		}
	}

	void SplashState::Update(float dt)
	{
		// if splash state has shown for as long as it should
		if (_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		{
			// replace splash state with main menu state
			_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
		}
	}

	void SplashState::Draw(float dt)
	{
		// clear the window, draw the background and display
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.display();
	}
}