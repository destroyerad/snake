
#include "Snake.hpp"
#include <iostream>
#include <cstdlib> // for rand()

Snake::Snake() : sSquareCount(20), length(1), appleNumber(3), appleValue(1)
{
    this->cLength = 1;
    this->total = sSquareCount * sSquareCount;
    this->grid = new int[total]();
    int pos;
    for (int i = 0; i < appleNumber; i++)
    {
        pos = randomRecursiveFind();
        this->grid[pos] = 1;
        this->apples.push_back(pos);
    }
    pos = (this->total % 2) ? this->total >> 1 : ((this->total - sSquareCount) >> 1) + sSquareCount * (rand() % 2) + rand() % 2 - 1;
    this->snakeHead = pos;
    this->grid[pos] = 2;
    this->snake.push_back(pos);
}

Snake::~Snake() { delete[] this->grid; }

void Snake::setGameWindow(SDL_Renderer* renderer, int windowSideSize)
{
    this->renderer = renderer;
    this->sSideSize = windowSideSize / this->sSquareCount;
}

void Snake::setDirection(int direction) 
{
    if (-direction != this->direction)
        this->direction = direction; 
}

int Snake::getWidth() { return this->sSquareCount; }

int Snake::update()
{
    int pHead = this->snakeHead;
    this->snakeHead += this->direction;

    if (onBorder(pHead, this->snakeHead) || onSnake())
        return -1;

    if (onApple()) {
        this->length += this->appleValue;
        for (size_t i = 0; i < this->apples.size(); ++i) {
            if (this->apples[i] == this->snakeHead) {
                this->apples.erase(this->apples.begin() + i);
                break;
            }
        }
        int newApplePos = randomRecursiveFind();
        this->grid[newApplePos] = 1;
        this->apples.push_back(newApplePos);
    } else {
        int tail = this->snake.front();
        this->snake.erase(this->snake.begin());
        this->grid[tail] = 0;
    }

    this->snake.push_back(this->snakeHead);
    this->grid[this->snakeHead] = 2;

    return 0;
}
void Snake::render()
{
    SDL_Rect rect;
    rect.w = this->sSideSize;
    rect.h = this->sSideSize;
    SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 255);
    for (auto& apple : this->apples)
    {
        rect.x = (apple % this->sSquareCount) * this->sSideSize;
        rect.y = apple / this->sSquareCount * this->sSideSize;
        SDL_RenderFillRect(this->renderer, &rect);
    }
    SDL_SetRenderDrawColor(this->renderer, 0, 255, 0, 255);
    for (auto& cell : this->snake)
    {
        rect.x = (cell % this->sSquareCount) * this->sSideSize;
        rect.y = cell / this->sSquareCount * this->sSideSize;
        SDL_RenderFillRect(this->renderer, &rect);
    }
}

int Snake::randomRecursiveFind()
{
    int rNumber;
    do {
        rNumber = rand() % this->total;
    } while (grid[rNumber] != 0);
    return rNumber;
}

bool Snake::onBorder(int pHead, int cHead)
{
    if (pHead % sSquareCount == 0 && cHead % sSquareCount == sSquareCount - 1 ||
            pHead % sSquareCount == sSquareCount - 1 && cHead % sSquareCount == 0 ||
            cHead >= this->total || cHead < 0)
        return true;
    return false;
}

bool Snake::onSnake()
{
    return this->grid[this->snakeHead] == 2;
}

bool Snake::onApple()
{
    return this->grid[this->snakeHead] == 1;
}

