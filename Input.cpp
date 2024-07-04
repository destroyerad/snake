#include "Input.hpp"

void Input::doEvent(SDL_Event* e, bool* run, int gWidth)
{
    SDL_Keycode key;
    this->mKeyPressed = false;
    while (SDL_PollEvent(e))
    {
        this->nMoveKey = false;
        switch (e->type)
        {
            case SDL_QUIT:
                *run = false;
                break;
            case SDL_KEYDOWN:
                key = e->key.keysym.sym;
                if (!this->nMoveKey && this->mKeyPressed)
                    this->nextKey = key;
                doMovement(&key, gWidth);
                break;
            default:
                break;
        }
    }
    if (!this->mKeyPressed && this->nextKey)
        doMovement(&this->nextKey, gWidth);
    this->nextKey = 0;
}

int Input::getDirection() { return this->direction; }

void Input::doMovement(SDL_Keycode* key, int gWidth)
{
    switch (*key)
    {
        case SDLK_w:
            this->direction = -gWidth;
            this->mKeyPressed = true;
            break;
        case SDLK_a:
            this->direction = -1;
            this->mKeyPressed = true;
            break;
        case SDLK_s:
            this->direction = gWidth;
            this->mKeyPressed = true;
            break;
        case SDLK_d:
            this->direction = 1;
            this->mKeyPressed = true;
            break;
        default:
            this->nMoveKey = true;
            break;
    }
}
