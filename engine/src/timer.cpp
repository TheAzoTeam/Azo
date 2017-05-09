#include "timer.hpp"

engine::Timer::Timer(){
	Reset();
}
engine::Timer::~Timer(){}

void engine::Timer::Reset(){
	start_ticks = SDL_GetTicks();
	elapsed_ticks = 0.0f;
	delta_time = 0.0f;
}

void engine::Timer::DeltaTime(){
	delta_time = SDL_GetTicks() - elapsed_ticks;
}

float engine::Timer::GetDeltaTime(){
	return delta_time;
}

void engine::Timer::Step(){
	elapsed_ticks = SDL_GetTicks();
}
