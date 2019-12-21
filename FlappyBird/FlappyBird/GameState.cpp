#include <sstream>
#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include "GameOverState.hpp"
#include <iostream>

namespace Gabijects
{
	// constructor saves game data reference
	GameState::GameState(GameDataRef data) : _data(data) {}

	void GameState::Init()
	{
		// load all sounds to their buffer
		if (!_hitSoundBuffer.loadFromFile(HIT_SOUND_FILEPATH))
		{
			std::cout << "Error loading Hit Sound Effect" << std::endl;
		}

		if (!_pointSoundBuffer.loadFromFile(POINT_SOUND_FILEPATH))
		{
			std::cout << "Error loading Point Sound Effect" << std::endl;
		}

		if (!_wingSoundBuffer.loadFromFile(WING_SOUND_FILEPATH))
		{
			std::cout << "Error loading Wing Sound Effect" << std::endl;
		}

		// set all sounds from their buffers
		_hitSound.setBuffer(_hitSoundBuffer);
		_pointSound.setBuffer(_pointSoundBuffer);
		_wingSound.setBuffer(_wingSoundBuffer);

		// load all textures needed for background, pipes, land, birds and font
		_data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		_data->assets.LoadTexture("Land", LAND_FILEPATH);

		_data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
		_data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
		_data->assets.LoadTexture("Scoring Pipe", SCORING_PIPE_FILEPATH);
		
		_data->assets.LoadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
		_data->assets.LoadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
		_data->assets.LoadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
		_data->assets.LoadTexture("Bird Frame 4", BIRD_FRAME_4_FILEPATH);
		
		_data->assets.LoadFont("Flappy Font", FLAPPY_FONT_FILEPATH);

		// initialise pointers with game data ref
		land = new Land(_data);
		pipe = new Pipe(_data);
		bird = new Bird(_data);
		flash = new Flash(_data);
		hud = new HUD(_data);

		// set background's texture
		_background.setTexture(this->_data->assets.GetTexture("Game Background"));

		// start score at 0 and update it in HUD
		_score = 0;
		hud->UpdateScore(_score);

		// set game state as ready
		_gameState = GameStates::eReady;
	}

	void GameState::HandleInput()
	{
		sf::Event event;

		// while there are events on window
		while (_data->window.pollEvent(event))
		{
			// if the event is that the window is closed, close window
			if (event.type == sf::Event::Closed)
			{
				_data->window.close();
			}

			// if the background has been clicked with left mouse button on window
			if (_data->input.IsSpriteClicked(_background, sf::Mouse::Left, _data->window))
			{
				// and if the game is not over yet
				if (_gameState != GameStates::eGameOver)
				{
					// set game state to playing and tap bird
					_gameState = GameStates::ePlaying;
					bird->Tap();

					// play wing sound
					_wingSound.play();
				}
			}
		}
	}

	void GameState::Update(float dt)
	{
		// if game is not over yet
		if (_gameState != GameStates::eGameOver)
		{
			// animate bird and move land
			bird->Animate(dt);
			land->MoveLand(dt);
		}

		// if game is being played
		if (_gameState == GameStates::ePlaying)
		{
			// move pipes
			pipe->MovePipes(dt);

			// if it's time, spawn pipes
			if (_clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY)
			{
				// randomise pipe position
				pipe->RandomisePipeOffset();

				// spawn pipes, top and bottom are shown, invisible
				// is not, and scoring is used for scoring purposes only
				pipe->SpawnInvisiblePipe();
				pipe->SpawnBottomPipe();
				pipe->SpawnTopPipe();
				pipe->SpawnScoringPipe();

				// restart clock
				_clock.restart();
			}

			// update bird
			bird->Update(dt);

			// get land sprites
			std::vector<sf::Sprite> landSprites = land->GetSprites();

			// go thru all land sprites
			for (int i = 0; i < landSprites.size(); i++)
			{
				// if there's a collision between bird and land sprite
				if (collision.CheckSpriteCollision(bird->GetSprite(), 0.7f, landSprites.at(i), 1.0f))
				{
					// game is over, and restart the clock
					_gameState = GameStates::eGameOver;
					_clock.restart();

					// play hit sound
					_hitSound.play();
				}
			}

			// get pipe sprites
			std::vector<sf::Sprite> pipeSprites = pipe->GetSprites();

			// go thru all pipe sprites
			for (int i = 0; i < pipeSprites.size(); i++)
			{
				// if there's a collision between bird and pipe sprite
				if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, pipeSprites.at(i), 1.0f))
				{
					// game is over, and restart the clock
					_gameState = GameStates::eGameOver;
					_clock.restart();

					// play hit sound
					_hitSound.play();
				}
			}

			// to-do: check if bird has touched top of the window (shoudl be game over then also)

			// get scoring sprites
			std::vector<sf::Sprite> &scoringSprites = pipe->GetScoringSprites();

			// go thru all scoring sprites
			for (int i = 0; i < scoringSprites.size(); i++)
			{
				// if there's a collision between bird and scoring sprite
				if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, scoringSprites.at(i), 1.0f))
				{
					// increment score by 1, update it in HUD and erase scoring sprite
					_score++;
					hud->UpdateScore(_score);
					scoringSprites.erase(scoringSprites.begin() + i);

					// play score sound
					_pointSound.play();
				}
			}
		}

		// if game is over
		if (_gameState == GameStates::eGameOver)
		{
			// show flash screen
			flash->Show(dt);

			// wait until it's time to show game over screen
			if (_clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APPEARS)
			{
				// replace game state with game over state in states stack
				_data->machine.AddState(StateRef(new GameOverState(_data, _score)), true);
			}
		}
	}

	void GameState::Draw(float dt)
	{
		// clear window
		_data->window.clear();
		// draw window background, pipes, land, bird, flash and HUD
		_data->window.draw(_background);
		pipe->DrawPipes();
		land->DrawLand();
		bird->Draw();
		flash->Draw();
		hud->Draw();
		// display in window
		_data->window.display();
	}
}