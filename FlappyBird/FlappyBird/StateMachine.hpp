#pragma once

#include <memory>
#include <stack>
#include "State.hpp"

namespace Gabijects
{
	typedef std::unique_ptr<State> StateRef;

	class StateMachine
	{
	public:
		// Empty constructor and destructor
		StateMachine() {}
		~StateMachine() {}
		
		// Adds or replaces state to state stack (doesn't process change)
		void AddState(StateRef newState, bool isReplacing = true);
		// Remove top state from state stack (doesn't process change)
		void RemoveState();
		// Process above changes
		void ProcessStateChanges();

		// Returns state on top of stack
		StateRef &GetActiveState();

	private:
		std::stack<StateRef> _states;	// stack with states with top being current state
		StateRef _newState;				// new state reference
		bool _isRemoving;				// true if removing state
		bool _isAdding;					// true if adding state
		bool _isReplacing;				// true if replacing state
	};
}