#ifndef TIMER_HPP
#define TIMER_HPP

#include "sdl2include.h"

namespace engine {
	class Timer {
		private:
			unsigned int startTicks;
			unsigned int elapsedTicks;
			float deltaTime;
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
