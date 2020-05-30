#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <string>

#include "Entity.h"

class Enemy : public Entity {
public:
    Enemy(SDL_Renderer* renderer);
    ~Enemy();

    void Update();
    void Render();
    bool IsAlive();

private:
    SDL_Texture* texture_;
    SDL_Rect collider_;
    bool alive_;
    float velocity_;
    std::vector<std::string> files_ = {"../res/BigEnemy.png", "../res/SmallEnemy.png"};
};

#endif