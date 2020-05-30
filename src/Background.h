#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Entity.h"

class Background : public Entity {
public:
    Background(SDL_Renderer* renderer);
    ~Background();

    void Update();
    void Render();

private:
    SDL_Texture* texture_;
};

#endif