#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity {
public:
    Player(SDL_Renderer* renderer);
    ~Player();

    void Update();
    void Render();
    void HandleInput();

private:
    SDL_Texture* texture_;
    float velocity_;
};

#endif