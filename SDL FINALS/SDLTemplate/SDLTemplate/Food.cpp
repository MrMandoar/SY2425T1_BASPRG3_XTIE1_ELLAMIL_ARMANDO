#include "Food.h"
#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL_image.h>

Food::Food(int cellSize) : cellSize(cellSize) {
    srand(time(0));  // randomizerer
}

void Food::spawn(const std::vector<std::pair<int, int>>& snakeBody) {
    bool valid = false;

    while (!valid) {
        position.first = rand() % 20; 
        position.second = rand() % 20;  

        // snek is eat yes ?
        valid = true;
        for (auto& segment : snakeBody) {
            if (segment == position) {
                valid = false;  // food no spawn on snek
                break;
            }
        }
    }
}

void Food::render(SDL_Renderer* renderer) {
    SDL_Texture* textureFood = IMG_LoadTexture(renderer, "Food.jpg");

    SDL_Rect rect = { position.first * cellSize, position.second * cellSize, cellSize, cellSize };
    SDL_RenderCopy(renderer, textureFood, nullptr, &rect);

    // Clean up 
    SDL_DestroyTexture(textureFood);
}

std::pair<int, int> Food::getPosition() const {
    return position;
}
