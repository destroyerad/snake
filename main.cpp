
#include "App.hpp"
#include <stdint.h>
#include <cstdlib>
#include <time.h>

const char* TITLE = "Snake";
const int FPS = 1000.0f / 10;

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    uint32_t frameStart, frameTime;
    App::Instance()->App::init(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            Window.width, Window.height, SDL_WINDOW_SHOWN);
    while (App::Instance()->App::running())
    {
        frameStart = SDL_GetTicks();
        App::Instance()->App::handleKeyboard();
        App::Instance()->App::update();
        App::Instance()->App::render();
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FPS)
            SDL_Delay((int)(FPS - frameTime));
    }
    App::Instance()->clean();
    return 0;
}
