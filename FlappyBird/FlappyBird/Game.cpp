#include "Game.hpp"
#include "SplashState.hpp"

#include <stdlib.h>
#include <time.h>

namespace Gabijects
{
	Game::Game(int width, int height, std::string title)
	{
		srand(time(NULL));

		// create window using sfml video mode and width and height passed,
		// as well as title, and sfml styles for closing window and for titlebar
		_data->window.create(sf::VideoMode(width, height), title, 
			sf::Style::Close | sf::Style::Titlebar);

		// add splash state to state machine
		_data->machine.AddState(StateRef(new SplashState(this->_data)));

		// run the game
		this->Run();
	}

	void Game::Run()
	{
		// keep track of time variables
		float newTime, frameTime, interpolation;

		// get current time as elapsed time as seconds
		float currentTime = this->_clock.getElapsedTime().asSeconds();
		// start accumulator at 0
		float accumulator = 0.0f;

		// while the window is open, the game is on
		while (this->_data->window.isOpen())
		{
			// process any state changes that might've occured
			this->_data->machine.ProcessStateChanges();

			// get new time as elapsed time as seconds
			newTime = this->_clock.getElapsedTime().asSeconds();
			// get frame time as new time - current time
			frameTime = newTime - currentTime;

			// limit frame time to 0.25 seconds
			if (frameTime > 0.25f)
			{
				frameTime = 0.25f;
			}

			// set current time to new time
			currentTime = newTime;
			// increment accumulator by frame time
			accumulator += frameTime;

			// whie accumulator is bigger or equal to delta timing
			while (accumulator >= dt)
			{
				// handle any input from the active state and update it
				this->_data->machine.GetActiveState()->HandleInput();
				this->_data->machine.GetActiveState()->Update(dt);

				// decrement accumulator by delta timing
				accumulator -= dt;
			}

			// get interpolation from accumulator / delta timing and draw using it
			interpolation = accumulator / dt;
			this->_data->machine.GetActiveState()->Draw(interpolation);
		}
	}
}