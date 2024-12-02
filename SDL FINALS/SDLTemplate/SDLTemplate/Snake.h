#ifndef SNAKE_H
#define SNAKE_H

#include <SDL.h>
#include <vector>
#include <utility>
#include "Food.h"

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Snake {
public:
    Snake(int startX, int startY, int cellSize);  // Constructor to initialize snake with position
    void move();  // Move the snake based on its current direction
    void render(SDL_Renderer* renderer);  // Render the snake to the screen
    void setDirection(Direction newDirection);  // Set the snake's direction
    bool checkCollision();  // Check for collisions with walls or self
    bool checkFoodCollision(Food& food);  // Check if snake eats food (parameter Food)
    void grow();  // Make the snake grow by adding a segment
    void increaseSpeed();  // Increase the snake's speed as it grows
    std::vector<std::pair<int, int>> body;  // The snake's body
    // Getter function for body
    const std::vector<std::pair<int, int>>& getBody() const {
        return body;
    }

private:
    
    Direction direction;  // Current direction of the snake
    int cellSize;  // The size of each grid cell
    int speed;  // Snake's speed
};

#endif  // SNAKE_H
