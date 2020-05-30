#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "Background.h"
#include "Timer.h"

#define FPS 60
#define FPS_TICKS 1000 / FPS

class Game {
public:
    Game();
    ~Game();

    bool Init();
    void Run();

private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;

    unsigned int lastTick_, fpsTick_, fps_, frameCount_;

    Background* background_;
    Timer* fpsTimer_;
    Timer* capTimer_;

    void Clean();
    void Update();
    void Render();
};

#endif