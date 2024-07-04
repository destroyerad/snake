#include "App.hpp"
#include <iostream>

App* App::instance = 0;

App::App(): window(0), renderer(0), run(false){};

App::~App() {
    window = 0;
    renderer = 0;
}

void App::init(const char* title, int x, int y, int w, int h, int flags)
{
    if (SDL_Init(SDL_WINDOW_SHOWN) == -1)
    {
        std::cout << "SDL failed to initialize! SDL_Error: " << SDL_GetError() << std::endl;
        run = false;
        return ;
    }
    window = SDL_CreateWindow(title, x, y, w, h, flags);
    if (window == NULL)
    {
        std::cout << "Failed to create window! SDL_Error: " << SDL_GetError() << std::endl;
        run = false;
        return ;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (IMG_Init(IMG_INIT_PNG) == -1)
    {
        std::cout << "Failed to intialize IMG! IMG_Error: " << IMG_GetError() << std::endl;
        run = false;
        return ;
    }
    if (TTF_Init() == -1)
    { 
        std::cout << "Failed to initialize TTF! TTF_Error: " << TTF_GetError() << std::endl;
        run = false;
        return ;
    }
    run = true;
    this->snake.setGameWindow(renderer, Window.width);
}

bool App::running() { return this->run; }

void App::handleKeyboard()
{
    SDL_Event e;
    this->input.doEvent(&e, &run, this->snake.getWidth());
    int direction = this->input.getDirection();
    this->snake.setDirection(direction);
}

void App::update()
{
    if (this->input.getDirection())
    {
        int state = this->snake.update();
        if (state == -1)
            run = false;
    }
}

void App::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    this->snake.render();
    SDL_RenderPresent(renderer);
}

void App::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

App* App::Instance()
{
    if (instance == 0)
    {
        instance = new App();
    }
    return instance;
}

SDL_Renderer* App::getRenderer() { return this->renderer; }
