#include "Background.h"

Background::Background(SDL_Renderer* renderer) : Entity(renderer) {
    SDL_Surface* surface = IMG_Load("../res/Background.png");
    texture_ = SDL_CreateTextureFromSurface(renderer, surface);
    width = surface->w;
    height = surface->h;
    SDL_FreeSurface(surface);
    x = 0;
    y = 0;
}

Background::~Background() { SDL_DestroyTexture(texture_); }

void Background::Update() {}

void Background::Render() {
    SDL_Rect dstRect;
    dstRect.x = 0;
    dstRect.y = 0;
    dstRect.w = width;
    dstRect.h = height;
    SDL_RenderCopy(renderer, texture_, 0, &dstRect);
}