#include<SDL.h>

class Pigeon{
    public:
    SDL_Texture* assets;
    // SDL_Renderer* renderer;
    SDL_Rect src[3];
    int frame=0;
    SDL_Rect mover = {50,50,50,50};
    void draw(SDL_Renderer*);
    Pigeon(SDL_Texture*);
    Pigeon();
};
