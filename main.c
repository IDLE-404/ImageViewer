#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s image.ppm\n", argv[0]);
        return 1;
    }

    FILE *in = fopen(argv[1], "rb");
    if (!in) {
        perror("fopen");
        return 1;
    }

    char line[256];

    fgets(line, sizeof(line), in);

    int width = -1, height = -1;
    fgets(line, sizeof(line), in);
    sscanf(line, "%d %d", &width, &height);
    fgets(line, sizeof(line), in);

    printf("width=%d height=%d\n", width, height);

    // --- SDL ---
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "PPM Viewer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        0
    );

    if (!window) {
        printf("Window error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *surface = SDL_GetWindowSurface(window);

    // --- Draw pixels ---
    SDL_Rect pixel = {0, 0, 1, 1};

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            Uint8 r = fgetc(in);
            Uint8 g = fgetc(in);
            Uint8 b = fgetc(in);

            Uint32 color = SDL_MapRGB(surface->format, r, g, b);

            pixel.x = x;
            pixel.y = y;
            SDL_FillRect(surface, &pixel, color);
        }
    }

    SDL_UpdateWindowSurface(window);

    // --- Event loop ---
    int running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = 0;
        }
        SDL_Delay(16);
    }

    // --- Cleanup ---
    fclose(in);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
