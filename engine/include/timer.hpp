#ifndef TIMER_HPP
#define TIMER_HPP

#include "sdl2include.h"

namespace engine {
	class Timer {
		private:
			unsigned int start_ticks;
			unsigned int elapsed_ticks;
			float delta_time;
		public:
			Timer();
			~Timer();

			void Reset();
			void DeltaTime();
			void Step();
			float GetDeltaTime();
	};
}

#endif
