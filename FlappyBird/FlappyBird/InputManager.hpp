#pragma once

#include <SFML/Graphics.hpp>

namespace Gabijects
{
	class InputManager
	{
	public:
		// Empty constructor and destructor
		InputManager() {}
		~InputManager() {}

		// Method to check if a sprite object is clicked by a mouse button on the sfml window
		bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);
		// Method for getting mouse position in sfml window
		sf::Vector2i GetMousePosition(sf::RenderWindow &window);
	};
}