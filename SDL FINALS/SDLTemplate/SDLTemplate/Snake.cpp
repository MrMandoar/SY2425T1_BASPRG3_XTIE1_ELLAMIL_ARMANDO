#include "Snake.h"
#include <SDL.h>
#include <iostream>
#include <vector>
#include <SDL_image.h>

Snake::Snake(int startX, int startY, int cellSize) : cellSize(cellSize), direction(Direction::RIGHT), speed(100) {
    body.push_back({ startX, startY });
}

void Snake::move() {
    std::pair<int, int> newHead = body.front();

    switch (direction) {
    case Direction::UP: newHead.second -= 1; break;
    case Direction::DOWN: newHead.second += 1; break;
    case Direction::LEFT: newHead.first -= 1; break;
    case Direction::RIGHT: newHead.first += 1; break;
    }

    body.insert(body.begin(), newHead);  // make long
    body.pop_back();  // tail go bye bye
}

void Snake::render(SDL_Renderer* renderer) {
    SDL_Texture* textureHead = IMG_LoadTexture(renderer, "Head.jpg");  
    SDL_Texture* textureBody = IMG_LoadTexture(renderer, "Body.jpg");  
    SDL_Texture* textureTail = IMG_LoadTexture(renderer, "Tail.jpg");  

    for (size_t i = 0; i < body.size(); ++i) {
        SDL_Rect rect = { body[i].first * cellSize, body[i].second * cellSize, cellSize, cellSize };
        if (i == 0) {
            SDL_RenderCopy(renderer, textureHead, nullptr, &rect);  // Head
        }
        else if (i == body.size() - 1) {
            SDL_RenderCopy(renderer, textureTail, nullptr, &rect);  // Tail
        }
        else {
            SDL_RenderCopy(renderer, textureBody, nullptr, &rect);  // Body
        }
    }

    // Clean up 
    SDL_DestroyTexture(textureHead);
    SDL_DestroyTexture(textureBody);
    SDL_DestroyTexture(textureTail);
}

void Snake::setDirection(Direction newDirection) {
    direction = newDirection;
}

bool Snake::checkCollision() {
    // snek is stupid ?
    if (body.front().first < 0 || body.front().first >= 20 || body.front().second < 0 || body.front().second >= 20) {
        return true; // snek is head bonk ?
    }

    for (size_t i = 1; i < body.size(); ++i) {
        if (body[i] == body.front()) {
            return true;  // snek is eat self ?
        }
    }

    return false;
}

bool Snake::checkFoodCollision(Food& food) {
    // snek is nomnom ?
    return (body.front().first == food.getPosition().first && body.front().second == food.getPosition().second);
}

void Snake::grow() {
    body.push_back(body.back());  // new tail liek lizard boi
}

void Snake::increaseSpeed() {
    if (speed > 20) {
        speed -= 10;  // snek go zoom every 5 food
    }
}
