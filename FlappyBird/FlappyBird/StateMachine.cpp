#include "StateMachine.hpp"

namespace Gabijects
{
	void StateMachine::AddState(StateRef newState, bool isReplacing)
	{
		// set is adding to true, and is replacing to what is passed
		this->_isAdding = true;
		this->_isReplacing = isReplacing;
		// add new state to new state variable
		this->_newState = std::move(newState);
	}

	void StateMachine::RemoveState()
	{
		// set is removing to true
		this->_isRemoving = true;
	}

	void StateMachine::ProcessStateChanges()
	{
		// if state is being removed and states stack isn't empty
		if (this->_isRemoving && !this->_states.empty())
		{
			// pop state on top of stack
			this->_states.pop();

			// if states stack still isn't empty
			if (!this->_states.empty())
			{
				// resume top state
				this->_states.top()->Resume();
			}

			// state been removed, set is removing to false
			this->_isRemoving = false;
		}

		// if state is being added
		if (this->_isAdding)
		{
			// if states stack isn't empty
			if (!this->_states.empty())
			{
				// and state is also replacing
				if (this->_isReplacing)
				{
					// pop state on top of stack
					this->_states.pop();
				}
				// otherwise, pause state on top of stack
				else 
				{
					this->_states.top()->Pause();
				}
			}

			// push new state to top of states stack and initialise it
			this->_states.push(std::move(this->_newState));
			this->_states.top()->Init();

			// state has been added, set is adding to false
			this->_isAdding = false;
		}
	}

	StateRef &StateMachine::GetActiveState()
	{
		// return state on top of stack
		return this->_states.top();
	}
}