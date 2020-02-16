#include <iostream>
#include "./Constants.h"
#include "./Game.h"

Game::Game()
{
    this->isRunning = false;
}

Game::~Game()
{

}

bool Game::IsRunning() const 
{
    return this->isRunning;

}

float projectilePositionX = 0.0f;
float projectilePositionY = 0.0f;
float projectileVelocityX = 20.0f;
float projectileVelocityY = 30.0f;

void Game::Initialize(int width, int height)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }

    window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_BORDERLESS
    );

    if(!window)
    {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if(!renderer)
    {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    isRunning = true;
    return;

}

void Game::ProcessInput()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;

        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE) 
            {
                isRunning = false;
            }
            break;

        default:
            break;
    }
}

void Game::Update()
{
    // Wait for 16ms target since last frame.
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), ticksOfLastFrame + FRAME_TARGET_TIME));

    // Delta time is a difference in ticks from last frame converted into seconds.
    float deltaTime = (SDL_GetTicks() - ticksOfLastFrame) / 1000.0f;

    // Clamp deltaTime to max value
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    // New ticks for current frame in the next pass
    ticksOfLastFrame = SDL_GetTicks();

    projectilePositionX += projectileVelocityX * deltaTime;
    projectilePositionY += projectileVelocityY * deltaTime;
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    SDL_Rect projectile 
    {
        (int) projectilePositionX,
        (int) projectilePositionY,
        10,
        10
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &projectile);

    SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
