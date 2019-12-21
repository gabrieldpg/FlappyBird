#include "Pipe.hpp"
#include <iostream>

namespace Gabijects
{
	// constructor saves game data reference
	Pipe::Pipe(GameDataRef data) : _data(data) 
	{
		// set land height to land's texture's height
		_landHeight = _data->assets.GetTexture("Land").getSize().y;
		// start spawn offset to 0
		_pipeSpawnYOffset = 0;
	}

	void Pipe::SpawnBottomPipe()
	{
		// set bottom pipe's texture to a sprite
		sf::Sprite sprite(_data->assets.GetTexture("Pipe Up"));
		// set sprite's position to the right in 
		// the x axis and a random place in the y axis
		sprite.setPosition(_data->window.getSize().x, 
			_data->window.getSize().y - sprite.getGlobalBounds().height - _pipeSpawnYOffset);
		// push new bottom sprite to pipe sprites vector
		pipeSprites.push_back(sprite);
	}

	void Pipe::SpawnTopPipe()
	{
		// set top pipe's texture to a sprite
		sf::Sprite sprite(_data->assets.GetTexture("Pipe Down"));
		// set sprite's position to the right in 
		// the x axis and a random place in the y axis
		sprite.setPosition(_data->window.getSize().x, -_pipeSpawnYOffset);
		// push new top sprite to pipe sprites vector
		pipeSprites.push_back(sprite);
	}

	void Pipe::SpawnInvisiblePipe()
	{
		// set invisible pipe's texture (won't show on screen)
		sf::Sprite sprite(_data->assets.GetTexture("Pipe Up"));
		// set sprite's position to the right in 
		// the x axis and centre in the y axis
		sprite.setPosition(_data->window.getSize().x, 
			_data->window.getSize().y - sprite.getGlobalBounds().height);
		// set its color to invisible
		sprite.setColor(sf::Color(0, 0, 0, 0));
		// push new invisible pipe to pipe sprites vector
		pipeSprites.push_back(sprite);
	}

	void Pipe::SpawnScoringPipe()
	{
		// set scoring pipe's texture
		sf::Sprite sprite(_data->assets.GetTexture("Scoring Pipe"));
		// set sprite's position to right in x axis and top on y axis
		sprite.setPosition(_data->window.getSize().x, 0);
		// push new scoring pipe to scoring pipes vector
		scoringPipes.push_back(sprite);
	}

	void Pipe::MovePipes(float dt)
	{
		// go through all pipe sprites
		for (unsigned short int i = 0; i < pipeSprites.size(); i++)
		{
			// if current pipe sprite has gone off the screen to the left
			if (pipeSprites.at(i).getPosition().x < 0 - pipeSprites.at(i).getGlobalBounds().width)
			{
				// erase this pipe sprite
				pipeSprites.erase(pipeSprites.begin() + i);
			}
			// if pipe sprite's still on the screen
			else				
			{
				// move it left by its speed
				float movement = PIPE_MOVEMENT_SPEED * dt;
				pipeSprites.at(i).move(-movement, 0);
			}

		}

		// go through all scoring pipes
		for (unsigned short int i = 0; i < scoringPipes.size(); i++)
		{
			// if current scoring pipe sprite has gone off the screen to the left
			if (scoringPipes.at(i).getPosition().x < 0 - scoringPipes.at(i).getGlobalBounds().width)
			{
				// erase this scoring pipe sprite
				scoringPipes.erase(scoringPipes.begin() + i);
			}
			// if pipe sprite's still on the screen
			else
			{
				// move it left by its speed
				float movement = PIPE_MOVEMENT_SPEED * dt;
				scoringPipes.at(i).move(-movement, 0);
			}
		}
	}

	void Pipe::DrawPipes()
	{
		// go through all pipe sprites and draw them
		for (unsigned short int i = 0; i < pipeSprites.size(); i++)
		{
			_data->window.draw(pipeSprites.at(i));
		}
	}

	void Pipe::RandomisePipeOffset()
	{
		_pipeSpawnYOffset = rand() % (_landHeight + 1);
	}

	const std::vector<sf::Sprite> &Pipe::GetSprites() const
	{
		return pipeSprites;
	}

	std::vector<sf::Sprite> &Pipe::GetScoringSprites()
	{
		return scoringPipes;
	}
}