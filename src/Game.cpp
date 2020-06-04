#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>

#include "Game.h"

Game::Game() {
    window_ = NULL;
    renderer_ = NULL;
}

Game::~Game() {}

bool Game::Init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    window_ = SDL_CreateWindow("DodgySquare", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window_) {
        return false;
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer_) {
        return false;
    }

    Message("Dodgy Square");  // Title screen
    HighScore("../high_score.txt");  // High score

    title_ = true;
    lastTick_ = SDL_GetTicks();
    fpsTick_ = lastTick_;
    fps_ = 0;
    frameCount_ = 0;

    return true;
}

void Game::Message(std::string message) {
    TTF_Font* font = TTF_OpenFont("../res/OpenSans-Regular.ttf", 24);
    SDL_Color color = {255, 255, 255};
    SDL_Surface* msg = TTF_RenderText_Solid(font, message.c_str(), color);

    titleTexture_ = SDL_CreateTextureFromSurface(renderer_, msg);

    titleRect_.x = (SCREEN_WIDTH / 2) - (msg->w / 2);
    titleRect_.y = (SCREEN_HEIGHT / 2) - (msg->h / 2);
    titleRect_.w = msg->w;
    titleRect_.h = msg->h;

    SDL_FreeSurface(msg);
    TTF_CloseFont(font);
}

void Game::HighScore(std::string path) {
    std::string line, high;
    std::string high_score = "High Score: ";
    std::ifstream filestream(path);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            linestream >> high;
            high_score += high;
        }
    }

    TTF_Font* font = TTF_OpenFont("../res/OpenSans-Regular.ttf", 24);
    SDL_Color color = {255, 255, 255};
    SDL_Surface* msg = TTF_RenderText_Solid(font, high_score.c_str(), color);

    highScoreTexture_ = SDL_CreateTextureFromSurface(renderer_, msg);

    highScoreRect_.x = (SCREEN_WIDTH / 2) - (msg->w / 2);
    highScoreRect_.y = (SCREEN_HEIGHT / 2) - (msg->h / 2) + 30;
    highScoreRect_.w = msg->w;
    highScoreRect_.h = msg->h;
}

void Game::Clean() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
}

void Game::Run() {
    running_ = true;

    SDL_ShowCursor(SDL_DISABLE);  // Do not show the cursor

    fpsTimer_ = new Timer();
    capTimer_ = new Timer();

    frameCount_ = 0;

    fpsTimer_->Start();

    while (running_) {
        capTimer_->Start();
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    running_ = false;
                    break;
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_SPACE) {
                        if (title_) { 
                            NewGame();
                        }
                    }
            }
        }

        if (!title_) {
            player_->Move();

            fps_ = frameCount_ / (fpsTimer_->GetTicks() / 1000.0f);
            if (fps_ > 2000000) { fps_ = 0; }

            int random = rand() % 100;
            if (random < 20) {  // Spawn enemy squares randomly based on this chance
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

            if (CheckCollision()) {  // If a collision is detected, the game is over
                title_ = true;
            }
        }

        Update();
        Render();
    }

    for (auto enemy : enemies_) {
        delete enemy;
    }

    delete fpsTimer_;
    delete capTimer_;
    delete player_;

    Clean();
    TTF_Quit();
    SDL_Quit();
}

void Game::Update() {
    if (title_) {
    } else {
        for (auto enemy : enemies_) {
            enemy->Update();
        }

        // Remove enemies that are not alive
        for (size_t i = 0; i < enemies_.size(); ++i) {
            if (!enemies_[i]->IsAlive()) {
                delete enemies_[i];
                enemies_.erase(enemies_.begin() + i);
            }
        }
    }
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);

    if (title_) {
        SDL_RenderCopy(renderer_, titleTexture_, NULL, &titleRect_);
        SDL_RenderCopy(renderer_, highScoreTexture_, NULL, &highScoreRect_);
    } else {
        player_->Render();

        for (auto enemy : enemies_) {
            enemy->Render();
        }
    }
    SDL_RenderPresent(renderer_);
}

bool Game::CheckCollision() {
    for (auto enemy : enemies_) {
        if (player_->Collides(enemy)) {
            return true;
        }
    }
    return false;
}

void Game::NewGame() {
    enemies_.clear();  // Remove all enemy squares from the enemies_ vector
    title_ = false;
    player_ = new Player(renderer_);
}