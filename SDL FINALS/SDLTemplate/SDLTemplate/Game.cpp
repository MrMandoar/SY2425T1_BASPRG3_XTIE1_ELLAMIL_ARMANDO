#include "Game.h"
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <cstdlib>
#include <ctime>

// Default constructor
Game::Game() : window(nullptr), renderer(nullptr), isRunning(true), score(0), showHighScore(false), highScore(0) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        isRunning = false;
    }
    else {
        window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, SDL_WINDOW_SHOWN);
        if (!window) {
            std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
            isRunning = false;
        }
        else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (!renderer) {
                std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
                isRunning = false;
            }
        }
    }
    // Initialize SDL_image for loading textures
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "Failed to initialize SDL_image: " << IMG_GetError() << std::endl;
    }

    // Initialize the game
    snake = new Snake(10, 10, 32);  // Initialize snake at grid (10, 10) with cell size of 32
    food = new Food(32);            // Initialize food
    food->spawn(snake->getBody());  // Ensure food spawns in an empty tile
    srand(static_cast<unsigned int>(time(0))); // Seed the random generator
}

// Constructor that accepts SDL_Renderer
Game::Game(SDL_Renderer* renderer) : window(nullptr), renderer(renderer), isRunning(true), score(0), showHighScore(false), highScore(0) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        isRunning = false;
    }
    else {
        window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, SDL_WINDOW_SHOWN);
        if (!window) {
            std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
            isRunning = false;
        }
    }

    // Initialize SDL_image for loading textures
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "Failed to initialize SDL_image: " << IMG_GetError() << std::endl;
    }

    // Initialize the game
    snake = new Snake(10, 10, 32);  // Initialize snake at grid (10, 10) with cell size of 32
    food = new Food(32);            // Initialize food
    food->spawn(snake->getBody());  // Ensure food spawns in an empty tile
    srand(static_cast<unsigned int>(time(0))); // Seed the random generator
}

Game::~Game() {
    delete snake;
    delete food;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) isRunning = false;

        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_w: snake->setDirection(Direction::UP); break;
            case SDLK_s: snake->setDirection(Direction::DOWN); break;
            case SDLK_a: snake->setDirection(Direction::LEFT); break;
            case SDLK_d: snake->setDirection(Direction::RIGHT); break;
            case SDLK_r: restart(); break;
            case SDLK_h: showHighScore = true; break;
            }
        }
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_h) {
            showHighScore = false;
        }
    }
}

void Game::update() {
    snake->move();
    if (snake->checkCollision()) {
        isRunning = false;  // Snake died, end the game
    }

    // Check if the snake eats food
    if (snake->checkFoodCollision(*food)) {
        food->spawn(snake->getBody()); // Spawn new food
        score += 1;
        snake->grow();
        if (score > highScore) {
            highScore = score;  // Update high score
        }
    }

    // Increase speed as score increases
    if (score > 0 && score % 5 == 0) {
        snake->increaseSpeed();
    }
}

void Game::render() {
    SDL_RenderClear(renderer);

    // Render background
    background.render(renderer);

    // Render snake and food
    snake->render(renderer);
    food->render(renderer);

    // Render high score box
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White
    SDL_Rect scoreBox = { 10, 10, 200, 50 };
    SDL_RenderDrawRect(renderer, &scoreBox);
    SDL_RenderPresent(renderer);
}

void Game::restart() {
    score = 0;
    delete snake;
    snake = new Snake(10, 10, 32);  // Re  start snake at initial position
    food->spawn(snake->getBody()); // Ensure food spawns in an empty tile
}

bool Game::isGameRunning() const {
    return isRunning;
}

void Game::setRunning(bool runningStatus) {
    isRunning = runningStatus;
}
