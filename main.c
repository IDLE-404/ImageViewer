#include <stdio.h>
#include <SDL2/SDL.h>

int main(void){
    const int width = 900; 
    const int height = 800;

    SDL_Window *pwindow = SDL_CreateWindow("Images Views", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height, 0);
    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

    Uint8 r,g,b;
    r=0x1A;
    g = b = 0x22;
    Uint32 color = SDL_MapRGB(psurface->format,r,g,b);
    SDL_Rect pixel = (SDL_Rect){0,0,1,1};
    for ( int x=0; x<width; x++)
    {
  
        for(int y =0; y<height; y++){
            pixel.x =x;
            pixel.y =y;
            SDL_FillRect(psurface, &pixel, color);
        }
    }


    SDL_UpdateWindowSurface(pwindow);
    SDL_Delay(3000); 
}