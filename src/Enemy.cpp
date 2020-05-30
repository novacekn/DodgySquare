#include <stdlib.h>

#include "Enemy.h"

Enemy::Enemy(SDL_Renderer* renderer) : Entity(renderer) {
    int random = rand() % 2;
    std::string file = files_.at(random);
    SDL_Surface* surface = IMG_Load(file.c_str());
    texture_ = SDL_CreateTextureFromSurface(renderer, surface);
    alive_ = true;
    width = surface->w;
    height = surface->h;
    SDL_FreeSurface(surface);
    velocity_ = 4.0f;
    
    x = rand() % (SCREEN_WIDTH - (int)width);  // Spawn at random x coordinate
    y = -height;  // Spawn out of play screen

    collider_.x = width;
    collider_.y = height;
}

Enemy::~Enemy() { SDL_DestroyTexture(texture_); }

void Enemy::Update() {
    if (y < SCREEN_HEIGHT + height) {
        y += velocity_;
    } else {
        SDL_DestroyTexture(texture_);
        alive_ = false;
    }
}

void Enemy::Render() {
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = width;
    dstRect.h = height;
    SDL_RenderCopy(renderer, texture_, 0, &dstRect);
}

bool Enemy::IsAlive() { return alive_; }