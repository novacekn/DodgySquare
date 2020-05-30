#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer {
public:
    Timer();

    void Start();
    void Stop();

    Uint32 GetTicks();

    bool IsStarted();

private:
    Uint32 startTicks_;
    bool started_;
};

#endif