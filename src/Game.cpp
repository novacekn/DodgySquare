#include "Game.h"

Game::Game() {
    window_ = NULL;
    renderer_ = NULL;
}

Game::~Game() {}

bool Game::Init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window_ = SDL_CreateWindow("DodgySquare", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window_) {
        return false;
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer_) {
        return false;
    }

    lastTick_ = SDL_GetTicks();
    fpsTick_ = lastTick_;
    fps_ = 0;
    frameCount_ = 0;

    return true;
}

void Game::Clean() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
}

void Game::Run() {
    bool running = true;

    SDL_ShowCursor(SDL_DISABLE);  // Do not show the cursor

    background_ = new Background(renderer_);
    fpsTimer_ = new Timer();
    capTimer_ = new Timer();
    player_ = new Player(renderer_);

    frameCount_ = 0;

    fpsTimer_->Start();

    while (running) {
        capTimer_->Start();
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }

        player_->Move();

        fps_ = frameCount_ / (fpsTimer_->GetTicks() / 1000.0f);
        if (fps_ > 2000000) {
            fps_ = 0;
        }

        int random = rand() % 100;
        if (random < 25) {
            enemy_ = new Enemy(renderer_);
            enemies_.push_back(enemy_);
        }

        char buf[100];
        frameCount_++;
        int frameTicks = capTimer_->GetTicks();
        if (frameTicks < FPS_TICKS) {
            SDL_Delay(FPS_TICKS - frameTicks);
        }

        snprintf(buf, 100, "DodgySquare (FPS: %u)", fps_);
        SDL_SetWindowTitle(window_, buf);

        Update();
        Render();
    }

    for (auto enemy : enemies_) {
        delete enemy;
    }

    delete background_;
    delete fpsTimer_;
    delete capTimer_;
    delete player_;

    Clean();
    SDL_Quit();
}

void Game::Update() {
    for (auto enemy : enemies_) {
        enemy->Update();
        if (player_->Collides(enemy)) {  // Check if player collides with the enemy
        }
    }

    // Remove enemies that are not alive
    for (size_t i = 0; i < enemies_.size(); ++i) {
        if (!enemies_[i]->IsAlive()) {
            delete enemies_[i];
            enemies_.erase(enemies_.begin() + i);
        }
    }
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);

    background_->Render();
    player_->Render();

    for (auto enemy : enemies_) {
        enemy->Render();
    }

    SDL_RenderPresent(renderer_);
}