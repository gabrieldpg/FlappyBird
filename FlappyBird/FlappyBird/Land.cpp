#include "Land.hpp"
#include "DEFINITIONS.hpp"

namespace Gabijects
{
	// constructor saves game data reference
	Land::Land(GameDataRef data) : _data(data)
	{
		// set 2 sprites to land's texture
		sf::Sprite sprite(_data->assets.GetTexture("Land"));
		sf::Sprite sprite2(_data->assets.GetTexture("Land"));

		// set first sprite's position to the left
		// in the x axis and the bottom in the y axis
		sprite.setPosition(0, _data->window.getSize().y - sprite.getGlobalBounds().height);

		// set second sprite's position to the right
		// in the x axis and the bottom in the y axis
		sprite2.setPosition(sprite.getGlobalBounds().width, _data->window.getSize().y - sprite.getGlobalBounds().height);

		// push both sprites to land sprites
		_landSprites.push_back(sprite);
		_landSprites.push_back(sprite2);
	}

	void Land::MoveLand(float dt)
	{
		// go through all land sprites
		for (unsigned short int i = 0; i < _landSprites.size(); i++)
		{
			// move it left by its speed
			float movement = PIPE_MOVEMENT_SPEED * dt;
			_landSprites.at(i).move(-movement, 0.0f);

			// if land sprite has come out of the screen to the left
			if (_landSprites.at(i).getPosition().x < 0 - _landSprites.at(i).getGlobalBounds().width)
			{
				// make a vector2f at right in the x axis
				// and at land sprite's current position in the y axis
				sf::Vector2f position(_data->window.getSize().x, _landSprites.at(i).getPosition().y);

				// set current land sprite to new position
				_landSprites.at(i).setPosition(position);
			}

		}
	}

	void Land::DrawLand()
	{
		// go through all land sprites and draw them
		for (unsigned short int i = 0; i < _landSprites.size(); i++)
		{
			_data->window.draw(_landSprites.at(i));
		}
	}

	const std::vector<sf::Sprite> &Land::GetSprites() const
	{
		return _landSprites;
	}
}