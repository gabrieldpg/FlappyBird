#include <SFML/Graphics.hpp>

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 512

int main() {
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flappy Bird");

	while (window.isOpen()) {
		// handle events

		// update game logic

		// draw
		window.clear();
		// draw SFML objects
		window.display();
	}

	return EXIT_SUCCESS;
}