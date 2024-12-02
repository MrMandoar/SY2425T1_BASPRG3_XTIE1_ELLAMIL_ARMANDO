#include "Game.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include <ctime>

#ifdef _MSC_VER
#define SDL_MAIN_HANDLED
#endif

int SDL_main(int argc, char* argv[]) {
    // Initialize the game
    Game game;

    // Game loop
    while (game.isGameRunning()) {
        game.handleEvents();
        game.update();
        game.render();
    }

    return 0;
}
