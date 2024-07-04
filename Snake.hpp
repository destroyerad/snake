// Snake.hpp
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

class Snake
{
public:
    Snake();
    ~Snake();
    void setGameWindow(SDL_Renderer* renderer, int windowSideSize);
    void setDirection(int direction);
    int getWidth();
    int update();
    void render();
private:
    SDL_Renderer* renderer;
    int sSquareCount;
    int sSideSize;
    int total;
    int* grid;
    std::vector<int> snake;
    int cLength;
    int length;
    int snakeHead;
    int direction = 0;
    int deadCell = -1;
    std::vector<int> apples;
    int appleNumber;
    int appleValue;
    int appleEaten = -1;
    int randomRecursiveFind();
    bool onBorder(int pHead, int cHead);
    bool onSnake();
    bool onApple();
};
