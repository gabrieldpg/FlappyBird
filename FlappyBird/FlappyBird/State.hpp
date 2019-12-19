#pragma once

namespace Gabijects
{
	class State
	{
	public:
		virtual void Init() = 0;			// Initialises state and its resources
		virtual void HandleInput() = 0;		// Handles input
		virtual void Update(float dt) = 0;	// Updates state and its resources
		virtual void Draw(float dt) = 0;	// Draws updated changes
		virtual void Pause() {}				// Pauses state
		virtual void Resume() {}			// Resumes state
	};
}