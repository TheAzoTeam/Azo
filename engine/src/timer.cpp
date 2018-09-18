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

void Timer::deltaTime(){
	delta_time = SDL_GetTicks() - elapsed_ticks;
}

float Timer::getDeltaTime(){
	return delta_time;
}

void Timer::step(){
	elapsed_ticks = SDL_GetTicks();
}
