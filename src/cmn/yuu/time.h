#ifndef __YUU_TIME_H__
#define __YUU_TIME_H__

//http://lazyfoo.net/tutorials/SDL/44_frame_independent_movement/index.php

#include <ryoji/fixed_floats.h>
#include <SDL.h>

namespace yuu {
	namespace _d {
		RYOJI_MAKE_CONSTEXPR_FP(1000, 0)
	}

	// Responsibility: Ticks time.
	class Time
	{
	public:
		//Initializes variables
		Time();

		// Tick the clock
		void tick();

		//Gets the timer's time
		const Uint32& getTicksElapsed() const;

		template<typename T> T getTimeElpased() {
			return ticksElapased / _d::_1000p0<T>;
		}

	private:
		Uint32 currentTicks;
		Uint32 ticksElapased;
	};
}

#endif