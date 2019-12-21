#include "HUD.hpp"

#include <string>

namespace Gabijects
{
	// constructor saves game data reference
	HUD::HUD(GameDataRef data) : _data(data)
	{
		// set score text's font, its string starts at '0', set its size and color also
		_scoreText.setFont(_data->assets.GetFont("Flappy Font"));
		_scoreText.setString("0");
		_scoreText.setCharacterSize(128);
		_scoreText.setFillColor(sf::Color::White);

		// set score text's origin to its center and position to
		// the middle in the x axis and the top in the y axis
		_scoreText.setOrigin(_scoreText.getGlobalBounds().width / 2, _scoreText.getGlobalBounds().height / 2);
		_scoreText.setPosition(_data->window.getSize().x / 2, _data->window.getSize().y / 8);
	}

	void HUD::Draw()
	{
		_data->window.draw(_scoreText);
	}

	void HUD::UpdateScore(int score)
	{
		// update score text's string to current score
		_scoreText.setString(std::to_string(score));
	}
}