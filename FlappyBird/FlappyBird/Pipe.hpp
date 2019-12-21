#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <vector>
#include "DEFINITIONS.hpp"

namespace Gabijects
{
	class Pipe
	{
	public:
		// Empty constructor and destructor
		Pipe(GameDataRef data);

		// Set pipe sprite texture, position and add to its vector
		void SpawnBottomPipe();
		void SpawnTopPipe();
		void SpawnInvisiblePipe();
		void SpawnScoringPipe();

		// Move pipes to the left continuously
		void MovePipes(float dt);
		void DrawPipes();

		// Sets pipe spawn y offset randomly
		void RandomisePipeOffset();

		// Get constant reference to pipe sprites
		const std::vector<sf::Sprite> &GetSprites() const;
		// Get modifieable reference to scoring sprites
		std::vector<sf::Sprite> &GetScoringSprites();

	private:
		GameDataRef _data;
		std::vector<sf::Sprite> pipeSprites;
		std::vector<sf::Sprite> scoringPipes;

		int _landHeight;
		int _pipeSpawnYOffset;	// Y offset so pipes are in difference positions
	};
}