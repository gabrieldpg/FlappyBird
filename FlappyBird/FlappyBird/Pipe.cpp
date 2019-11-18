#include "Pipe.hpp"

namespace Gabijects
{
	Pipe::Pipe(GameDataRef data) : _data(data) {}

	void Pipe::DrawPipes()
	{
		for (unsigned short int i = 0; i < pipeSprites.size(); i++)
		{
			_data->window.draw(pipeSprites.at(i));
		}
	}
}