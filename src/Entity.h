#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640

class Entity {
public:
    Entity(SDL_Renderer* renderer);
    virtual ~Entity() = default;

    virtual void Update() = 0;
    virtual void Render() = 0;

    bool Collides(Entity* other);

    float x, y, width, height;

protected:
    SDL_Renderer* renderer;
};

#endif