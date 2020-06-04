#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Entity.h"

class Background : public Entity {
public:
    enum STATES { START, GAME, GAME_OVER };
    Background(SDL_Renderer* renderer);
    ~Background();

    void Update();
    void Render();

    unsigned int state;

private:
    SDL_Texture* texture_;
};

#endif