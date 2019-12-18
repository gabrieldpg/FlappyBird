#include "InputManager.hpp"

namespace Gabijects
{
	bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow & window)
	{
		// if mouse button is pressed
		if (sf::Mouse::isButtonPressed(button))
		{
			// get rectangle object from sprite's x and y as well as
			// global bounds width and height
			sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, 
				object.getGlobalBounds().width, object.getGlobalBounds().height);

			// if mouse click was done inside rectangle object within sfml window, return true
			if (tempRect.contains(sf::Mouse::getPosition(window)))
			{
				return true;
			}
		}
		return false;
	}

	sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow & window)
	{
		// return mouse position in relation to sfml window
		return sf::Mouse::getPosition(window);
	}
}