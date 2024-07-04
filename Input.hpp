#include <SDL2/SDL.h>
#include <iostream>

class Input
{
public:
    void doEvent(SDL_Event* e, bool* run, int gWidth);
    int getDirection();
private:
    int direction = 0;
    void doMovement(SDL_Keycode* key, int gWidth);
    bool mKeyPressed = false;
    bool nMoveKey = false;
    SDL_Keycode nextKey;
};
