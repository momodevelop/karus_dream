#include "time.h"

namespace yuu {

	Time::Time() : currentTicks(0), ticksElapased(0)
	{
	}

	void Time::tick()
	{
		ticksElapased = SDL_GetTicks() - currentTicks;
		currentTicks = SDL_GetTicks();
	}

	const Uint32& Time::getTicksElapsed() const
	{

		return ticksElapased;
	}
}