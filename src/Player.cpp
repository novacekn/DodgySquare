#include "Player.h"

Player::Player(SDL_Renderer* renderer) : Entity(renderer) {
    SDL_Surface* surface = IMG_Load("../res/Player.png");
    texture_ = SDL_CreateTextureFromSurface(renderer, surface);
    width = surface->w;
    height = surface->h;
    SDL_FreeSurface(surface);

    x = SCREEN_WIDTH / 2;
    y = SCREEN_HEIGHT - height;
    velocity_ = 5.0f;
}

Player::~Player() { SDL_DestroyTexture(texture_); }

void Player::Update() {}

void Player::Render() {
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = width;
    dstRect.h = height;
    SDL_RenderCopy(renderer, texture_, 0, &dstRect);
}

void Player::HandleInput() {
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);

    if (keystates[SDL_SCANCODE_W] && y >= 0) {
        y -= velocity_;
    }

    if (keystates[SDL_SCANCODE_S] && y <= SCREEN_HEIGHT - height) {
        y += velocity_;
    }

    if (keystates[SDL_SCANCODE_A] && x >= 0) {
        x -= velocity_;
    }

    if (keystates[SDL_SCANCODE_D] && x <= SCREEN_WIDTH - width) {
        x += velocity_;
    }
}