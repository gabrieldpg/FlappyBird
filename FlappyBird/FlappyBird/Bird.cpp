#include "Bird.hpp"

namespace Gabijects
{
	Bird::Bird(GameDataRef data) : _data(data)
	{
		// start animation iterator to 0 and add bird frames to vector
		_animationIterator = 0;
		_animationFrames.push_back(_data->assets.GetTexture("Bird Frame 1"));
		_animationFrames.push_back(_data->assets.GetTexture("Bird Frame 2"));
		_animationFrames.push_back(_data->assets.GetTexture("Bird Frame 3"));
		_animationFrames.push_back(_data->assets.GetTexture("Bird Frame 4"));

		// set bird sprite texture to current animation frame
		_birdSprite.setTexture(_animationFrames.at(_animationIterator));

		// set bird's position to left side on x axis and in the middle of the y axis
		_birdSprite.setPosition((_data->window.getSize().x / 4) - (_birdSprite.getGlobalBounds().width / 2),
			(_data->window.getSize().y / 2) - (_birdSprite.getGlobalBounds().height / 2));

		// set bird's state to still
		_birdState = BIRD_STATE_STILL;

		// set bird's origin to its current position
		sf::Vector2f origin = sf::Vector2f(_birdSprite.getGlobalBounds().width/2,
			_birdSprite.getGlobalBounds().height/2);

		_birdSprite.setOrigin(origin);

		_rotation = 0;
	}

	void Bird::Draw()
	{
		// draw bird sprite to window
		_data->window.draw(_birdSprite);
	}

	void Bird::Animate(float dt)
	{
		// if the bird animation duration has finished
		if (_clock.getElapsedTime().asSeconds() > BIRD_ANIMATION_DURATION / _animationFrames.size())
		{
			// UPDATE ANIMATION ITERATOR
			// if the animation iterator hasn't got to the last animation frame yet
			if (_animationIterator < _animationFrames.size() - 1)
			{
				// increment it
				_animationIterator++;
			}
			else
			{
				// otherwise, go back to first frame
				_animationIterator = 0;
			}

			// set bird's texture to current animation frame and restart the clock
			_birdSprite.setTexture(_animationFrames.at(_animationIterator));
			_clock.restart();
		}
	}

	void Bird::Update(float dt)
	{
		// if bird is falling
		if (_birdState == BIRD_STATE_FALLING)
		{
			// move bird sprite according to gravity and delta timing
			_birdSprite.move(0, GRAVITY * dt);
			// increment rotation by its speed times delta timing
			_rotation += ROTATION_SPEED * dt;

			// if rotation has gone over its maximum, set it to its maximum
			if (_rotation > MAX_ROTATION)
			{
				_rotation = MAX_ROTATION;
			}

			_birdSprite.setRotation(_rotation);
		}
		// if bird is flying
		else if (_birdState == BIRD_STATE_FLYING)
		{
			// move bird up by flying speed times delta timing
			_birdSprite.move(0, -FLYING_SPEED * dt);

			// decrement rotation speed times delta timing
			_rotation -= ROTATION_SPEED * dt;

			// if rotation at maximum negative rotation, set it to its negative maximum
			if (_rotation < -MAX_ROTATION)
			{
				_rotation = -MAX_ROTATION;
			}

			_birdSprite.setRotation(_rotation);
		}

		// if bird has flown its flying duration
		if (_movementClock.getElapsedTime().asSeconds() > FLYING_DURATION)
		{
			// restart movement clock and change bird's state to falling
			_movementClock.restart();
			_birdState = BIRD_STATE_FALLING;
		}
	}

	void Bird::Tap()
	{
		// restart movement clock and change bird's state to flying
		_movementClock.restart();
		_birdState = BIRD_STATE_FLYING;
	}

	const sf::Sprite &Bird::GetSprite() const
	{
		return _birdSprite;
	}
}