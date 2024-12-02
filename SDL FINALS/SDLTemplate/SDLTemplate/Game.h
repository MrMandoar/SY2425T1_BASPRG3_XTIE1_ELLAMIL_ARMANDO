#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Snake.h"
#include "Food.h"
#include "Background.h"

class Game {
public:
    Game();  // Default constructor
    Game(SDL_Renderer* renderer);  // Constructor that accepts SDL_Renderer
    ~Game();

    void handleEvents();
    void update();
    void render();
    void restart();
    bool isGameRunning() const;
    void setRunning(bool runningStatus);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
    int score;
    int highScore;
    bool showHighScore;
    Snake* snake;
    Food* food;
    Background background;
};

#endif
