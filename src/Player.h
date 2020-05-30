#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity {
public:
    Player(SDL_Renderer* renderer);
    ~Player();

    void Update();
    void Render();
    void Move();

private:
    SDL_Texture* texture_;
    SDL_Rect collider_;
    float velocity_;
};

#endif