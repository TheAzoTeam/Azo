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

float Timer::getDeltaTime() {
	return deltaTime;
}

void Timer::step() {
	elapsedTicks = SDL_GetTicks();
}
