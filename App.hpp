#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Input.hpp"
#include "Snake.hpp"
#include "structs.hpp"

class App
{
public:
    void init(const char* title, int x, int y, int w, int h, int flags);
    bool running();
    void handleKeyboard();
    void update();
    void render();
    void clean();
    static App* Instance();
    SDL_Renderer* getRenderer();
private:
    App();
    ~App();
    SDL_Window* window;
    SDL_Renderer* renderer;
    Snake snake;
    Input input;
    static App* instance;
    bool run;
};
