#ifndef MAIN_H
#define MAIN_H

#include <SDL.h>
#include "Game.h"  // Include your Game class header

class Main {
public:
    Main();  // Constructor to initialize SDL and game components
    ~Main();  // Destructor to clean up SDL and game

    void run();  // Method to run the game loop

private:
    SDL_Window* window;  // The SDL window
    SDL_Renderer* renderer;  // The SDL renderer
    Game* game;  // Game instance
};

#endif // MAIN_H
