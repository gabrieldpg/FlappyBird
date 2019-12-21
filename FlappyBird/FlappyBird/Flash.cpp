#include "Flash.hpp"

namespace Gabijects
{
	// constructor saves game data reference
	Flash::Flash(GameDataRef data) : _data(data)
	{
		// set rectangle shape to window size
		_shape = sf::RectangleShape(sf::Vector2f(_data->window.getSize()));
		// set its color to resemble a flash
		_shape.setFillColor(sf::Color(255, 255, 255, 0));
		// set flash on to true
		_flashOn = true;
	}

	void Flash::Show(float dt)
	{
		// if flash on is true, flash getting brighter
		if (_flashOn)
		{
			// get alpha from shapes color and add flash speed times delta timing to it
			int alpha = (int)_shape.getFillColor().a + (FLASH_SPEED * dt);

			// if alpha has reached its maximum
			if (alpha >= 255.0f)
			{
				// set it to its maximum
				alpha = 255.0f;
				// set flash on to false so it gets darker again
				_flashOn = false;
			}

			// set shapes color based on alpha
			_shape.setFillColor(sf::Color(255, 255, 255, alpha));
		}
		// if flash on is false, flash getting darker
		else
		{
			// get alpha from shapes color and subtract flash speed times delta timing to it
			int alpha = (int)_shape.getFillColor().a - (FLASH_SPEED * dt);

			// if alpha has reached its minimum
			if (alpha <= 0.0f)
			{
				// set it to its minimum
				alpha = 0.0f;
				// ensure flash on is false
				_flashOn = false;
			}

			// set shapes color based on alpha
			_shape.setFillColor(sf::Color(255, 255, 255, alpha));
		}
	}

	void Flash::Draw()
	{
		_data->window.draw(_shape);
	}
}