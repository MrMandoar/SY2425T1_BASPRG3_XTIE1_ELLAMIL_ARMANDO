#include "Background.h"

void Background::render(SDL_Renderer* renderer) {
    // Light gray
    SDL_SetRenderDrawColor(renderer, 211, 211, 211, 255); 

   
    SDL_RenderClear(renderer);
}
