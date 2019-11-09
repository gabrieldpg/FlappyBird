#include <SFML/Graphics.hpp>

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 512

int main() 
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flappy Bird");

	while (window.isOpen()) 
	{
		// handle events
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		// update game logic
		window.clear();

		// draw SFML objects
		window.display();
	}

	return EXIT_SUCCESS;
}