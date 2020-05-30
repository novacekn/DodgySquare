#include "Timer.h"

Timer::Timer() {
    startTicks_ = 0;
    started_ = false;
}

void Timer::Start() {
    started_ = true;
    startTicks_ = SDL_GetTicks();
}

void Timer::Stop() {
    started_ = false;
    startTicks_ = 0;
}

bool Timer::IsStarted() {
    return started_;
}

Uint32 Timer::GetTicks() {
    Uint32 time = 0;
    if (started_) {
        time = SDL_GetTicks() - startTicks_;
    }
    
    return time;
}