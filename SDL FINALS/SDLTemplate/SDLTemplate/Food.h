#ifndef FOOD_H
#define FOOD_H

#include <SDL.h>
#include <cstdlib>
#include <vector>
#include <utility>

class Food {
public:
    Food(int cellSize);  // food in cell yes
    void spawn(const std::vector<std::pair<int, int>>& snakeBody);  // food go
    void render(SDL_Renderer* renderer);  // food show
    std::pair<int, int> getPosition() const;  // food loc

private:
    std::pair<int, int> position;  // food loc
    int cellSize;  // cell size
};

#endif 
