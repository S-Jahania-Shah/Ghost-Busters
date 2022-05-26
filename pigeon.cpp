#include "pigeon.hpp"

void Pigeon::draw(SDL_Renderer *renderer){
    SDL_RenderCopy(renderer, assets, &src[frame], &mover);
    frame++;
    if (frame==3) frame = 0;
}

Pigeon::Pigeon(SDL_Texture* tex){
    src[0] = {0,0,160,133};
    src[1] = {0,133,160,133};
    src[2] = {0,266,160,133};
    assets = tex;
}

Pigeon::Pigeon(){
    src[0] = {0,0,160,133};
    src[1] = {0,133,160,133};
    src[2] = {0,266,160,133};
    assets = NULL;
}