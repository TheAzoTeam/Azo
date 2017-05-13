#include "timer.hpp"

using namespace engine;

Timer::Timer(){
	Reset();
}
Timer::~Timer(){}

void Timer::Reset(){
	start_ticks = SDL_GetTicks();
	elapsed_ticks = 0.0f;
	delta_time = 0.0f;
}

void Timer::DeltaTime(){
	delta_time = SDL_GetTicks() - elapsed_ticks;
}

float Timer::GetDeltaTime(){
	return delta_time;
}

void Timer::Step(){
	elapsed_ticks = SDL_GetTicks();
}
