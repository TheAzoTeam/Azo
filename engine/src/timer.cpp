#include "timer.hpp"

using namespace engine;

Timer::Timer() {
	Reset();
}
Timer::~Timer() {}

void Timer::Reset() {
	startTicks = SDL_GetTicks();
	elapsedTicks = 0.0f;
	deltaTime = 0.0f;
}

void Timer::DeltaTime() {
	deltaTime = SDL_GetTicks() - elapsedTicks;
}

float Timer::GetDeltaTime() {
	return deltaTime;
}

void Timer::Step() {
	elapsedTicks = SDL_GetTicks();
}
